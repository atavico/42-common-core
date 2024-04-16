import { environment } from '../../environments/environment';

const ip = environment.IP_ADDRESS;

export function getBaseUrl() {
  //console.log('ip:', ip);
  return `https://${ip}:8000`;
}

export function getWsUrl() {
  return `wss://${ip}:8001`;
}
