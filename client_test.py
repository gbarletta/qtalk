# thanks to GPT :>

import time
import random
import string
import socket
import struct

def random_string():
    # Choose a random length for the string (between 5 and 15 characters, for example)
    length = random.randint(10, 100)

    # Generate a random string with uppercase letters, lowercase letters, and digits
    characters = string.ascii_letters + string.digits
    random_str = ''.join(random.choices(characters, k=length))

    return random_str

def send_messages(ip, port):
    try:
        # Create a TCP socket
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        # Connect to the server
        client_socket.connect((ip, port))

        while True:
            message = "ciaoo"
            message_length = len(message)
            print(message)
            print(message_length)
            length_bytes = struct.pack('!H', message_length)

            client_socket.sendall(length_bytes)
            client_socket.sendall("ci".encode())
            client_socket.sendall("aoo".encode())

            if client_socket.recv(2).decode() == "ok":
                time.sleep(1)
            else:
                print("weird error")

    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    # Replace '127.0.0.1' with the actual IP address of the server
    ip_address = "127.0.0.1"

    # Replace 42069 with the actual port number of the server
    port_number = 42069

    # Call the function to send the message
    send_messages(ip_address, port_number)
