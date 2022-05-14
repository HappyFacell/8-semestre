import socket
from tkinter import SEPARATOR
import nacl.utils
import nacl.secret
from nacl.signing import SigningKey
from nacl.signing import VerifyKey

_key = nacl.utils.random(nacl.secret.SecretBox.KEY_SIZE)

USUARIOS_AUTENTICADOS = {
    "test@test.mx": "12345",
    "is722820@iteso.mx": "#HolaMundo12345",
}

f = open("secretInfo.txt", "w")


def EncriptarArchivo(informacionArchivo: bytes):
    # Encriptar el mensaje que nos ha enviado el cliente
    # llave
    box = nacl.secret.SecretBox(_key)
    # Encriptar la informacion
    encrypted = box.encrypt(bytes(informacionArchivo, 'utf-8'))
    # print(type(encrypted))

    f = open("secretInfo.txt", "a")
    f.write(f"Datos cifrados:\n {encrypted}\n")
    f.close()

    # Regresar el archivo encriptado
    return encrypted


def DesencriptarArchivo(infoArchivo):
    try:
        # print(type(infoArchivo))
        box = nacl.secret.SecretBox(_key)
        desencrypt = box.decrypt(infoArchivo)
        # print(desencrypt)

        f = open("secretInfo.txt", "a")
        f.write(f"Texto decifrado: \n{desencrypt}\n")
        f.close()

        return desencrypt

    except (ValueError, KeyError):
        print("Error en la desencriptacion del archivo")


def FirmaDeArchivo(informacionEncriptada: str):
    sign_key = SigningKey.generate()
    infoFirmada = sign_key.sign(informacionEncriptada)
    f = open("secretInfo.txt", "a")
    f.write(f'Informacion firmada: \n {infoFirmada}\n')
    f.close()
    return infoFirmada, sign_key


def ConfirmacionFirmaArchivos(infoFirmada, key: SigningKey):
    verify_key = VerifyKey(key.verify_key.encode())
    res = verify_key.verify(infoFirmada)
    f = open("secretInfo.txt", "a")
    f.write(f'Verificar firma: \n {res} \n')
    f.close()
    return res


def login(usr: str, pwd: str):
    file = open("users.txt", "a")
    if usr != "" and pwd != "":
        if usr in USUARIOS_AUTENTICADOS and pwd in USUARIOS_AUTENTICADOS.values():
            # Agregar quien entro a la bitacora
            file.write(f"-I- Entro el usuario: {usr}\n")
            file.write("\n")
            return True
    file.write(f"-E- Intento entrar el usuario: {usr}\n")
    file.write("\n")
    file.close()
    return False


def BitacoraAccesos():
    f = open("users.txt", "r")
    print(f.read())
    f.close()


if __name__ == "__main__":
    BUFFER_SIZE = 4096

    host = "127.0.0.1"
    port = 65432

    SEPARATOR = "<SEPARATOR>"

    s = socket.socket()

    # Bind the socket with the address and port
    s.bind((host, port))

    # Listen to the connection
    s.listen()
    # print(f"[*] Listening as {host}:{port}")

    # Block execution and waits for an incomming connection
    client_socket, address = s.accept()
    print(f"Connected by {address}")

    # Read whatever the client sends
    everything = client_socket.recv(BUFFER_SIZE).decode()
    message, user, pwd, fileName = everything.split(SEPARATOR)

    # Revisar si el usuario esta los usuarios registrados
    if not login(user, pwd):
        client_socket.sendall(f"User o pwd no valida: {user}".encode())

    else:
        # Cifrar el archivo
        print(f'Arhico cifrado')
        # archivoCifrado = cifrarArchivo(message)

        archivoCifrado = EncriptarArchivo(message)
        client_socket.sendall(f'Archivo cifrado: \n{archivoCifrado}'.encode())

        # Decifrar el archivo
        print(f'Decifrar el archivo')
        archivoDecifrado = DesencriptarArchivo(archivoCifrado)
        client_socket.sendall(
            f'Archivo Decifrado: \n{archivoDecifrado}'.encode())

        # Firmar el archivo encriptado
        print("Firmar el archivo")
        infoFirmada, key = FirmaDeArchivo(archivoCifrado)

        # Verificar la firma del arhivo
        print("Verificacion de firma")
        infoVerificada = ConfirmacionFirmaArchivos(infoFirmada, key)

        # Bitacora
        BitacoraAccesos()

    s.close()
