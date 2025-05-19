import grpc
import tkinter as tk
from tkinter import ttk

import proto.helloworld_pb2 as helloworld_pb2
import proto.helloworld_pb2_grpc as helloworld_pb2_grpc


def send_request(channel, name):
    stub = helloworld_pb2_grpc.GreeterStub(channel)
    response = stub.SayHello(helloworld_pb2.HelloRequest(name=name))
    return response.message


def main():
    root = tk.Tk()
    root.title("gRPC Client")

    frame = ttk.Frame(root, padding="10")
    frame.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))

    name_var = tk.StringVar()
    result_var = tk.StringVar()

    ttk.Label(frame, text="Name:").grid(row=0, column=0, sticky=tk.W)
    name_entry = ttk.Entry(frame, textvariable=name_var)
    name_entry.grid(row=0, column=1, sticky=(tk.W, tk.E))

    ttk.Button(frame, text="Send", command=lambda: result_var.set(send_request(channel, name_var.get()))).grid(row=1, column=0, columnspan=2)
    ttk.Label(frame, textvariable=result_var).grid(row=2, column=0, columnspan=2)

    for child in frame.winfo_children():
        child.grid_configure(padx=5, pady=5)

    root.mainloop()


if __name__ == "__main__":
    with grpc.insecure_channel("localhost:50051") as channel:
        main()
