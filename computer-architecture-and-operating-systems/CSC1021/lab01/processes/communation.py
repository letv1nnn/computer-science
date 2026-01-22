from multiprocessing import *
import time

def greet(q):
    print(f"(child process: {current_process().pid}) Waiting for names...")
    for _ in range(5):
        name = q.get()
        print(f"(child process: {current_process().pid}) Well, hi {name}")

def send_name():
    q = Queue()
    names = ["Artem", "Brady", "Mark", "Tim", "Ollie"]

    p1 = Process(target=greet, args=(q,))
    p1.start()

    for name in names:
        time.sleep(1.5)
        print(f"(parent process: {current_process().pid}): Ok, I'll send the name")
        q.put(name)

if __name__ == "__main__":
    send_name()

