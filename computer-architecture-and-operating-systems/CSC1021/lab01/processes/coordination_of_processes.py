from multiprocessing import *
import time

def slowpoke(lock):
    time.sleep(10)
    lock.acquire()
    print("Slowpoke: Ok, I'm coming")
    lock.release()

def have_to_wait():
    lock = Lock()
    p1 = Process(target=slowpoke, args=(lock,))
    p1.start()
    print("Waiter: Any day now...")

    p1.join()
    print("Waiter: Finally! Geez.")

def add_two_numbers(num1, num2, q):
    q.put(num1 + num2)

def add_two_params():
    n1, n2 = int(input("First number: ")), int(input("Second number: "))
    q = Queue()
    p = Process(target = add_two_numbers, args=(n1, n2, q))
    p.start()
    result = q.get()
    print(f"The result is {result}")

if __name__ == "__main__":
    # have_to_wait()
    add_two_params()
