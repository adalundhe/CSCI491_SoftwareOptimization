import matplotlib.pyplot as plt

num_elements = 4194304
cache_avg_time = 0.029446/num_elements
naive_avg_time = 0.65894/num_elements
element_no = []
cache_time = []
naive_time = []
break_points_cached = []
break_points_naive = []

cached_all = []
naive_all = []

for i in range(1,4194304 + 1):
    cached_all.append(cache_avg_time * i)
    naive_all.append(naive_avg_time * i)

for i in range(1,1025,32):
    cache_time.append(cache_avg_time * i)
    naive_time.append(naive_avg_time * i)
    element_no.append(i)

plt.plot(element_no,cache_time, 'bo', element_no, naive_time, 'ko')
plt.title('Cache Oblivious vs. Naive Tranposition Times (Per Element)')
# plt.xlim([0,4500000])
# plt.ylim([0,1])
plt.xlabel('Number of Elements')
plt.ylabel('Time (Sec)')
plt.annotate('L1',xy=(32,cached_all[32]), xytext=(0,cached_all[32]+0.00003), arrowprops=dict(facecolor='blue', shrink=0.000005))
plt.annotate('L2',xy=(128, cached_all[128]), xytext=(256,cached_all[32]+0.00003), arrowprops=dict(facecolor='blue', shrink=0.000001))
plt.annotate('L3',xy=(758,cached_all[768]+0.0000025), xytext=(768,cached_all[32]+0.00006), arrowprops=dict(facecolor='blue', shrink=0.000005))
plt.annotate('L1',xy=(32,naive_all[32]), xytext=(64, naive_all[32]+0.00003), arrowprops=dict(facecolor='black', shrink=0.000005))
plt.annotate('L2',xy=(125,naive_all[128]+0.0000025), xytext=(256, naive_all[32]+0.00006), arrowprops=dict(facecolor='black', shrink=0.000005))
plt.annotate('L3',xy=(754,naive_all[768]+0.0000025), xytext=(768, naive_all[768]+0.00003), arrowprops=dict(facecolor='black', shrink=0.000005))

plt.grid()
plt.show()
