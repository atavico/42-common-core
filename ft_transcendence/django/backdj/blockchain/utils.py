
abi = [
	{
		"anonymous": False,
		"inputs": [
			{
				"indexed": True,
				"internalType": "uint256",
				"name": "idMatch",
				"type": "uint256"
			},
			{
				"indexed": False,
				"internalType": "string",
				"name": "finals_s",
				"type": "string"
			},
			{
				"indexed": False,
				"internalType": "string",
				"name": "semi_finals_s",
				"type": "string"
			},
			{
				"indexed": False,
				"internalType": "string",
				"name": "quarters_s",
				"type": "string"
			},
			{
				"indexed": False,
				"internalType": "string",
				"name": "finals_w",
				"type": "string"
			},
			{
				"indexed": False,
				"internalType": "string",
				"name": "semi_finals_w",
				"type": "string"
			},
			{
				"indexed": False,
				"internalType": "string",
				"name": "quarters_w",
				"type": "string"
			},
			{
				"indexed": False,
				"internalType": "uint256",
				"name": "timestamp",
				"type": "uint256"
			}
		],
		"name": "MatchResultRecorded",
		"type": "event"
	},
	{
		"inputs": [
			{
				"internalType": "uint256",
				"name": "_idMatch",
				"type": "uint256"
			},
			{
				"components": [
					{
						"internalType": "string",
						"name": "finals",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "semi_finals",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "quarters",
						"type": "string"
					}
				],
				"internalType": "struct GameResults.Structure",
				"name": "_s",
				"type": "tuple"
			},
			{
				"components": [
					{
						"internalType": "string",
						"name": "finals",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "semi_finals",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "quarters",
						"type": "string"
					}
				],
				"internalType": "struct GameResults.Winners",
				"name": "_w",
				"type": "tuple"
			},
			{
				"internalType": "uint256",
				"name": "",
				"type": "uint256"
			}
		],
		"name": "recordMatchResult",
		"outputs": [],
		"stateMutability": "nonpayable",
		"type": "function"
	},
	{
		"inputs": [
			{
				"internalType": "uint256",
				"name": "idMatch",
				"type": "uint256"
			}
		],
		"name": "getMatch",
		"outputs": [
			{
				"internalType": "uint256",
				"name": "",
				"type": "uint256"
			},
			{
				"components": [
					{
						"internalType": "string",
						"name": "finals",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "semi_finals",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "quarters",
						"type": "string"
					}
				],
				"internalType": "struct GameResults.Structure",
				"name": "",
				"type": "tuple"
			},
			{
				"components": [
					{
						"internalType": "string",
						"name": "finals",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "semi_finals",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "quarters",
						"type": "string"
					}
				],
				"internalType": "struct GameResults.Winners",
				"name": "",
				"type": "tuple"
			},
			{
				"internalType": "uint256",
				"name": "",
				"type": "uint256"
			}
		],
		"stateMutability": "view",
		"type": "function"
	},
	{
		"inputs": [
			{
				"internalType": "uint256",
				"name": "",
				"type": "uint256"
			}
		],
		"name": "matchResults",
		"outputs": [
			{
				"internalType": "uint256",
				"name": "idMatch",
				"type": "uint256"
			},
			{
				"components": [
					{
						"internalType": "string",
						"name": "finals",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "semi_finals",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "quarters",
						"type": "string"
					}
				],
				"internalType": "struct GameResults.Structure",
				"name": "s",
				"type": "tuple"
			},
			{
				"components": [
					{
						"internalType": "string",
						"name": "finals",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "semi_finals",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "quarters",
						"type": "string"
					}
				],
				"internalType": "struct GameResults.Winners",
				"name": "w",
				"type": "tuple"
			},
			{
				"internalType": "uint256",
				"name": "timestamp",
				"type": "uint256"
			}
		],
		"stateMutability": "view",
		"type": "function"
	}
]
