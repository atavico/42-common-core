FROM python:3.8-alpine

ENV PYTHONUNBUFFERED 1
ENV PYTHONDONTWRITEBYTECODE 1

WORKDIR /app/backend

COPY requirements.txt /app/backend/

# Build psycopg2-binary from source -- add required required dependencies
RUN apk add --virtual .build-deps --no-cache gcc python3-dev musl-dev && \
        apk add libffi-dev && \
        apk add postgresql-client && \
        pip install --no-cache-dir -r requirements.txt && \
        apk --purge del .build-deps && \
                pip install hvac && \
                apk --no-cache add curl

COPY . /app/backend/

# CMD [ "python", "backdj/manage.py", "runserver", "0.0.0.0:8000" ]
CMD until pg_isready --username=$POSTGRES_USER --host=$POSTGRES_HOSTNAME; do sleep 1; done; \
                sleep 12; \
                source get-vault-credentials; \
        python backdj/manage.py makemigrations; \
        python backdj/manage.py migrate; \
        nohup python backdj/manage.py runsslserver \
                --certificate  tls-certificates/cert.pem \
                --key tls-certificates/key.pem \
                0.0.0.0:8000 \
                #> myscript.log 2>&1 \
                & \
        cd backdj && daphne \
            -e ssl:8001:privateKey=../tls-certificates/key.pem:certKey=../tls-certificates/cert.pem \
            backdj.asgi:application ; \
        # python backdj/manage.py runserver $IP_ADDR:8000
