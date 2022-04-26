import socket

HOST = "127.0.0.1"
PORT = 65432


def main() -> None:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        print("Mandando txt")
        with open("file_to_send.txt", "rb") as file: # abrimos el archivo a enviar y le asignamos un alias
            for line in file.readlines(): # Leemos el archivo linea por linea
                s.sendall(line) # Enviamos las lineas


if __name__ == "__main__":
    main() # Codigo usuario