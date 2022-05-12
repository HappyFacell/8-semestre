from abc import ABC
import base64
import nacl.secret
import nacl.utils

_key = nacl.utils.random(nacl.secret.SecretBox.KEY_SIZE)

def random() -> bytes:
  return base64.b64encode(nacl.utils.random())



def encrypt2(message: bytes) -> bytes:
  box = nacl.secret.SecretBox(_key)
  encrypted = box.encrypt(message)
  return encrypted


def decrypt2(message: bytes) -> bytes:
  box = nacl.secret.SecretBox(_key)
  desencrypt = box.decrypt(message)
  return desencrypt


if __name__ == "__main__":
  # for i in range(10):
  #   print("i: ",i)
  print(random())
  mensaje = b"Hola mundo"
  incriptado = encrypt2(mensaje)
  print(incriptado)
  desincriptado = decrypt2(incriptado)
  print(desincriptado)