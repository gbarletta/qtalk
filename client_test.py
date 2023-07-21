# thanks to GPT :>

import socket
import struct

def send_message(ip, port, message):
    try:
        # Create a TCP socket
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        # Connect to the server
        client_socket.connect((ip, port))

        # Convert the length of the message to a 2-byte value in network order
        message_length = len(message)
        length_bytes = struct.pack('!H', message_length)

        # Send the length bytes followed by the message
        client_socket.sendall(length_bytes + message.encode())

        # Close the socket
        client_socket.close()

        print("Message sent successfully.")
    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    # Replace '127.0.0.1' with the actual IP address of the server
    ip_address = "127.0.0.1"

    # Replace 42069 with the actual port number of the server
    port_number = 42069

    # Replace 'Hello, server!' with the message you want to send
    message_to_send = "Hello, server!"

    # Call the function to send the message
    send_message(ip_address, port_number, message_to_send)
