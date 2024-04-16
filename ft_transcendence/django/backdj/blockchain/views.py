
import json

from .blockchain import get_match 
from utilities.response import JSONResponse
from utilities.logger import printi
from rest_framework.decorators import api_view
from utilities.decorators import login_required

from django.conf import settings

# Create your views here.

def transform_back(ls:list) -> dict:
    return {
        "finals": json.loads(ls[0]),
        "semifinals": json.loads(ls[1]),
        "quarters": json.loads(ls[2])
    }

@login_required
@api_view(("GET", ))
def get_tournament_from_blockchain(request) -> JSONResponse:
    printi(request.GET)
    t_id = request.GET.get("tid")
    dct = {}
    res = get_match(int(t_id) + settings.BLOCKCHAIN_ID)
    if res == None:
        return JSONResponse(
            error_code=400,
            message="Blockchain transaction still being evaluated",
            data=[],
        )

    dct["winners"] = transform_back(res[2])
    dct["structure"] = transform_back(res[1])
    dct["id"] = res[0]
    dct["timestamp"] = res[3]

    return JSONResponse(
        error_code=200,
        message="Blockchain transaction evaluated",
        data=dct
    )