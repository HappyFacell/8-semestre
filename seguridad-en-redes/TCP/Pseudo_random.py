import base64
import nacl.utils

def random() -> bytes:
  return base64.b64encode(nacl.utils.random())


if __name__ == "__main__":
  # for i in range(10):
  #   print("i: ",i)
  print(random())