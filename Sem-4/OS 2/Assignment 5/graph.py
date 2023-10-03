import numpy as np
import matplotlib.pyplot as plt

# 1) Average time(Constant writers)
number_of_reader_threads = np.array([1, 5, 10, 15, 20])
rw_w = np.array([104.05, 121.5, 120.05, 119.679, 113])
rw_r = np.array([107.9, 23.05, 15.64, 10.75, 8.59])
frw_w = np.array([105.67, 158.02, 185.45, 183.02, 196.87])
frw_r = np.array([108.043, 173.67, 189.67, 200.23, 210.567])

plt.plot(number_of_reader_threads, rw_r*1.5, c="yellow", label="(a) RW: Reader", marker="o")
plt.plot(number_of_reader_threads, frw_r*1.5, c="orange", label="(a) Fair RW: Reader", marker="o")
plt.plot(number_of_reader_threads, rw_w*1.5, c="blue", label="(b) RW: Writer", marker="o")
plt.plot(number_of_reader_threads, frw_w*1.5, c="purple", label="(b) Fair RW: Writer", marker="o")

plt.title("Average waiting times(Constant Writers)")
plt.xlabel("Number of Reader threads -->")
plt.ylabel("Average waiting time(milliseconds) -->")
plt.legend()
plt.ylim(0)
plt.xlim(0)
plt.grid()

plt.show()

# 2) Average time(Constant reader)
number_of_writer_threads = np.array([1, 5, 10, 15, 20])
rw_w = np.array([7.61, 11.78, 100.57, 234.14, 360.23])
rw_r = np.array([0.5, 1.17, 18.5, 24.34, 31.07])
frw_w = np.array([5.08, 28, 217.34, 293.05, 500.09])
frw_r = np.array([4.69, 29.06, 220.97, 310.5, 538.9])

plt.plot(number_of_writer_threads, rw_r*1.5, c="yellow", label="(a) RW: Reader", marker="o")
plt.plot(number_of_writer_threads, frw_r*1.5, c="orange", label="(a) Fair RW: Reader", marker="o")
plt.plot(number_of_writer_threads, rw_w*1.5, c="blue", label="(b) RW: Writer", marker="o")
plt.plot(number_of_writer_threads, frw_w*1.5, c="purple", label="(b) Fair RW: Writer", marker="o")

plt.title("Average waiting times(Constant Readers)")
plt.xlabel("Number of Writer threads -->")
plt.ylabel("Average waiting time(milliseconds) -->")
plt.legend()
plt.ylim(0)
plt.xlim(0)
plt.grid()

plt.show()


# 3) Worst case time(Constant writers)
number_of_reader_threads = np.array([1, 5, 10, 15, 20])
rw_w = np.array([293.05, 304.5, 294.03, 432.2, 404.34])
rw_r = np.array([137.97, 172.04, 180.5, 140.23, 190.34])
frw_w = np.array([273.34, 329.45, 380.9, 332.78, 353.69])
frw_r = np.array([248.05, 351.67, 349.12, 361.05, 333.35])

plt.plot(number_of_reader_threads, rw_r*1.5, c="yellow", label="(a) RW: Reader", marker="o")
plt.plot(number_of_reader_threads, frw_r*1.5, c="orange", label="(a) Fair RW: Reader", marker="o")
plt.plot(number_of_reader_threads, rw_w*1.5, c="blue", label="(b) RW: Writer", marker="o")
plt.plot(number_of_reader_threads, frw_w*1.5, c="purple", label="(b) Fair RW: Writer", marker="o")

plt.title("Worst case waiting times(Constant Writers)")
plt.xlabel("Number of Reader threads -->")
plt.ylabel("Worst case waiting time(milliseconds) -->")
plt.legend()
plt.ylim(0)
plt.xlim(0)
plt.grid()

plt.show()

# 4) Worst case time(Constant reader)
number_of_writer_threads = np.array([1, 5, 10, 15, 20])
rw_w = np.array([67.15, 152.04, 295.27, 452.6, 559.6])
rw_r = np.array([37.65, 65.69, 205.89, 300.69, 445.7])
frw_w = np.array([69, 151, 449.07, 496, 675.87])
frw_r = np.array([67, 189, 410, 466, 722])

plt.plot(number_of_writer_threads, rw_r*1.5, c="yellow", label="(a) RW: Reader", marker="o")
plt.plot(number_of_writer_threads, frw_r*1.5, c="orange", label="(a) Fair RW: Reader", marker="o")
plt.plot(number_of_writer_threads, rw_w*1.5, c="blue", label="(b) RW: Writer", marker="o")
plt.plot(number_of_writer_threads, frw_w*1.5, c="purple", label="(b) Fair RW: Writer", marker="o")

plt.title("Worst case waiting times(Constant Readers)")
plt.xlabel("Number of Writer threads -->")
plt.ylabel("Worst case waiting time(milliseconds) -->")
plt.legend()
plt.ylim(0)
plt.xlim(0)
plt.grid()

plt.show()