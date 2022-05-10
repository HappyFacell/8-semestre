import socket
from nacl.signing import SigningKey

HOST = "127.0.0.1"
PORT = 65432


def main() -> None:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        print("Mandando txt")
        with open("file_to_send.txt", "rb") as file: # abrimos el archivo a enviar y le asignamos un alias
            read = file.read()
            # Generate a new random signing key
            signing_key = SigningKey.generate()

            # Sign a message with the signing key
            signed = signing_key.sign(read)

            # Obtain the verify key for a given signing key
            verify_key = signing_key.verify_key
            # Serialize the verify key to send it to a third party
            verify_key_bytes = verify_key.encode()
            
            s.send(verify_key_bytes)
            s.send(signed.signature)
            s.send(read)
            


if __name__ == "__main__":
    main() # Codigo usuario