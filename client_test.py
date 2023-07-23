import time
import random
import string
import socket
import struct

def random_string():
    return "".join(random.choices(string.ascii_letters + string.digits, k=random.randint(10, 100)))

def send_messages(ip, port):
    try:
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client_socket.connect((ip, port))

        while True:
            data = bytearray()
            rand_str = random_string()
            print(rand_str)
            data.append(0x02) # start
            data.extend("rm16".encode("utf-8"))
            data.append(0x1c)
            data.extend("produce".encode("utf-8"))
            data.append(0x1c)
            data.extend("topic_test".encode("utf-8"))
            data.append(0x1c)
            data.extend(rand_str.encode("utf-8"))
            data.append(0x03) # actual end
        
            client_socket.send(data)
            time.sleep(2)

    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    ip_address = "127.0.0.1"
    port_number = 42069
    send_messages(ip_address, port_number)
