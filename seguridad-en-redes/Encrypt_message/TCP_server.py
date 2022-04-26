import socket
import Pseudo_random

HOST = "127.0.0.1"
PORT = 65432


def main() -> None:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        print("Conectado y esperando respuesta")
        s.bind((HOST, PORT))
        s.listen()
        conn, addr = s.accept()
        with conn:
            print(f"Connected by {addr}")
            file_data = b"" # Datos del archivo
            file_data2 = b"" # Datos del archivo
            while True:
                data = conn.recv(1024)
                if not data:
                    break
                file_data += Pseudo_random.encrypt2(data) # Guardamos los datos recibidos para escribirlos en el archivo de servidor
                file_data2 += Pseudo_random.decrypt2(file_data)

    with open("file_to_recive_encrypt.txt", "wb") as file: # Creamos el archivo y escribimos en el
        file.write(file_data)
    with open("file_to_recive_decrypt.txt", "wb") as file: # Creamos el archivo y escribimos en el
        file.write(file_data2)


if __name__ == "__main__":
    main()