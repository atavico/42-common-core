
import json
from .utils import abi
from utilities.logger import printd, printi
from django.conf import settings
from web3 import Web3

BLOCK = settings.BLOCK
try:
	BlockWeb = Web3(Web3.HTTPProvider(BLOCK['url']))
	if BlockWeb.is_connected():
		# print('Connected with the Ethereum Network')
		BLOCK['balance'] = BlockWeb.eth.get_balance(BLOCK['wallet'])
		BLOCK['sepholia_eth_balance'] = BLOCK['balance'] / 10**18
		# print('Wallet balance:', BLOCK['sepholia_eth_balance'], 'SPH_ETH')
	else:
		printd('Not connected with the Ethereum Network')

	contract_address = BLOCK['smart']
	contract = BlockWeb.eth.contract(address=contract_address, abi=abi)

	web3 = BlockWeb
	my_wallet_address = BLOCK['wallet']
	metamask_private_key = BLOCK['key']
	smart_contract_address = BLOCK['smart']
	wei_balance = BLOCK['balance']
	sepholia_eth_balance = BLOCK['sepholia_eth_balance']
	printd("Blockchain initialized successfully")
except Exception as e:
	printd(f"Blockchain cannot be initialized -> {e}")

#TODO: insert match variables
# def record_match(match):
# 	transaction = contract.functions.recordMatchResult(
# 		5, 
# 		('0-5','1-0','3-4'),
# 		('DIO','Prova','EMA'),
# 		10,
# 		).build_transaction({
# 	   'from': my_wallet_address,
# 	   'gas': 1000000,
# 	   'gasPrice': web3.to_wei('50', 'gwei'),
# 	   'nonce': web3.eth.get_transaction_count(my_wallet_address)
# 	})

# 	signed_tx = web3.eth.account.sign_transaction(transaction, metamask_private_key)
# 	tx_hash = web3.eth.send_raw_transaction(signed_tx.rawTransaction)
# 	print('Transaction hash:', tx_hash.hex())



#TODO: check match info variables (return)
def get_match(id_match_required:int=0):
	try:
		match_info = contract.functions.getMatch(id_match_required).call()
		printi(f"TXHash returned match: {match_info}")
		return match_info
	except Exception as e:
		printd(f"Cannot get match -> {e}")
		return None


#######################################TRANSACTION#############################################
def tournament_transaction(body:dict): # body = to_tournament structure
	try:
		printi(f"Blockchain body: {body}")
		transaction = contract.functions.recordMatchResult(
			body['id'], 
			body['structure'],
			body['winners'],
			10,
			).build_transaction({
		   'from': my_wallet_address,
		   'gas': 1000000,
		   'gasPrice': web3.to_wei('50', 'gwei'),
		   'nonce': web3.eth.get_transaction_count(my_wallet_address)
		})

		# Firma della transazione
		signed_tx = web3.eth.account.sign_transaction(transaction, metamask_private_key)
		tx_hash = web3.eth.send_raw_transaction(signed_tx.rawTransaction)
		printi(f"Transaction hash: {tx_hash.hex()}")

		return tx_hash
	except Exception as e:
		printd(f"Cannot store tournament in blockchain -> {e}")
		return None
