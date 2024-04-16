FROM hashicorp/vault
COPY policy.hcl /policy.hcl
COPY setup-and-run-vault /setup-and-run.sh

RUN chmod +x /setup-and-run.sh

COPY vault.hcl /vault.hcl
COPY tls-certificates /tls-certificates
COPY policy-credentials-token.hcl /policy-credentials-token.hcl
COPY elk-credentials-token.hcl /elk-credentials-token.hcl
COPY elk-admin-token.hcl /elk-admin-token.hcl
CMD /setup-and-run.sh
