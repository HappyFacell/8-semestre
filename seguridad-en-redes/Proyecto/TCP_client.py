# mandar el archivo para que el server lo encripte y firme
import socket
from tkinter import SEPARATOR
from tkinter.filedialog import askopenfilename

BUFFER_SIZE = 4096

SEPARATOR = "<SEPARATOR>"

host = "127.0.0.1"
port = 65432

def login():
    print("User: ")
    user = input(str())
    print("Password: ")
    pwd = input(str())
    user_pwd = [user, pwd]
    return user_pwd

def openFile() -> str:
    filename = askopenfilename()
    return filename

if __name__ == "__main__":

    myInfo = login()

    myFileName = openFile()
    
    with open(myFileName, 'rb') as fileDataToRead:
        message = fileDataToRead.read()
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, port))

    s.sendall(f"{message}{SEPARATOR}{myInfo[0]}{SEPARATOR}{myInfo[1]}{SEPARATOR}{myFileName}".encode())
    data = s.recv(BUFFER_SIZE)
    print(data.decode())
