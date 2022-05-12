import socket
import json
import Pseudo_random
from base64 import b64decode, b64encode
from tkinter import SEPARATOR
import nacl.utils
from nacl.signing import SigningKey
from nacl.signing import VerifyKey
from tkinter import SEPARATOR

USUARIOS_AUTENTICADOS = {
    "user1@correo.mx": "12345",
    "user2@correo.mx": "98765",
}

f = open("secrets.txt", "w")

def cifrarArchivo(informacionArchivo: bytes):
    # Encriptar el mensaje que nos ha enviado el cliente
    # llave
    chacha20_key = nacl.utils.random()

    # Chacha baby
    # chachaCipher = ChaCha20.new(key=chacha20_key)

    # Encriptar la informacion
    texto_encriptado = Pseudo_random.encrypt2(informacionArchivo)


    f = open("secrets.txt", "a")
    f.write(f"Datos cifrados:\n {texto_encriptado}\n")
    f.close()
    
    # Regresar el archivo encriptado
    return texto_encriptado

def decifrarArchivo(infoArchivo:str, key:bytes):
    try:
        b64 = json.loads(infoArchivo)
        cipherText = b64decode(b64['ciphertext'])
        textoDecifrado = Pseudo_random.decrypt2(cipherText)
        
        f = open("secrets.txt", "a")
        f.write(f"Texto decifrado: \n{textoDecifrado}\n")
        f.close()
        # print(type(textoDecifrado.decode('utf-8')))

        return textoDecifrado.decode('utf-8')

    except (ValueError, KeyError):
        print("Error en la desencriptacion del archivo")
    

def firmaDeArchivo(informacionEncriptada:str):
    sign_key = SigningKey.generate()
    infoFirmada = sign_key.sign(informacionEncriptada)
    f = open("secrets.txt", "a")
    f.write(f'Informacion firmada: \n {infoFirmada}\n')
    f.close()
    return infoFirmada, sign_key


def verificacionFirmaArchivos(infoFirmada, key:SigningKey):
    verify_key = VerifyKey(key.verify_key.encode())
    # print(verify_key.verify(infoFirmada))
    res = verify_key.verify(infoFirmada)
    f = open("secrets.txt", "a")
    f.write(f'Verificar firma: \n {res} \n')
    f.close()
    return res 


def login(usr: str, pwd: str):
    file = open("bitacora.txt", "a")
    if usr != "" and pwd != "":
        if usr in USUARIOS_AUTENTICADOS and pwd in USUARIOS_AUTENTICADOS.values():
            # Agregar quien entro a la bitacora
            file.write(f"+ Entro el usuario: {usr}\n")
            file.write("\n")
            return True
    file.write(f"- Intento entrar el usuario: {usr}\n")
    file.write("\n")
    file.close()
    return False


def bitacoraAccesos():
    f = open("bitacora.txt", "r")
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

    #Listen to the connection
    s.listen()
    print(f"[*] Listening as {host}:{port}")

    # Block execution and waits for an incomming connection
    client_socket, address = s.accept()

    # Read whatever the client sends
    everything = client_socket.recv(BUFFER_SIZE).decode()
    message, user, pwd, fileName = everything.split(SEPARATOR)

    # Revisar si el usuario esta los usuarios registrados
    if not login(user, pwd):
        client_socket.sendall(f"User o pwd no valida: {user}".encode())

    else:
        # Cifrar el archivo
        print(f'Arhico cifrado')
        archivoCifrado, decrypt, key = cifrarArchivo(message)
        client_socket.sendall(f'Archivo cifrado: \n{archivoCifrado}'.encode())

        # Decifrar el archivo
        print(f'Decifrar el archivo')
        archivoDecifrado = decifrarArchivo(decrypt, key)
        client_socket.sendall(f'Archivo cifrado: \n{archivoDecifrado}'.encode())
        
        # Firmar el archivo encriptado
        print("Firmar el archivo")
        infoFirmada, key =  firmaDeArchivo(archivoCifrado)

        # Verificar la firma del arhivo
        print("Verificacion de firma")
        infoVerificada = verificacionFirmaArchivos(infoFirmada, key)

        # Bitacora
        bitacoraAccesos()

    s.close()