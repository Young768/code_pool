import matplotlib.pyplot as plt
import numpy as np
import re

filepath = 'build-php'
print("test")
data1 = []
data2 = []
with open(filepath) as fp:
   line = fp.readline()
   result = "Time To Compile:"
   print(result)
   cnt = 0
   while line:
       if result in line:
           arr = []
           for x in range(6):
               if (x >=1 ):
                line = fp.readline()
                ansi_escape = re.compile(r'\x1B\[[0-?]*[ -/]*[@-~]')
                a = ansi_escape.sub('', line)
                x = float(a)
                arr.append(x)
                cnt += 1
           sd = np.std(arr)
           ave = np.mean(arr)
           data1.append(ave)
           data2.append(sd)

       line = fp.readline()
bar = []
bar.append(0.0)
for i in data1:
    tmp = ( data1[6]-i)/data1[6]
    bar.append(tmp)
    print(tmp)
bar.append(0.0)


bar1 = []
bar1.append(0.0)
for j in data2:
    tmp1 = j/data1[6]
    bar1.append(tmp1)
    print(tmp1)
bar1.append(0.0)
objects = ('0','Previous', 'ClearLinux', 'OverLoad','NoAffine', 'FirstIdle', 'CFS', 'LowMigr', 'HighMigr', '')
y_pos = np.arange(len(objects))

fig = plt.figure()
fig.suptitle('crafty', fontsize=14, fontweight='bold')
#e = [0.5, 1., 1.5, 2. , .5, 1., 1.5, 2.]
plt.errorbar(y_pos, bar, yerr=bar1, fmt='o')
plt.xticks(y_pos, objects)
plt.plot([0,1,2,3,4,5,6,7,8,9], [0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0],'r')
plt.setp(plt.gca().get_xticklabels(), rotation=45, horizontalalignment='right')
plt.show()




#print(cnt)
#plt.plot(data)
#plt.ylabel('some numbers')
#plt.show()