import numpy as np
import math
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import scipy
from scipy.special import erf


# measurments 

N_ABC = [1, 5, 3, 10, 25, 28, 101, 147, 222, 229, 239, 255, 236, 237, 253, 235, 234, 246, 244, 249, 227, 246, 237, 239, 234 ]                              # events counted by A, B, and C 
N_AC = [297, 314, 298, 314, 292, 283, 314, 276, 328, 294, 291, 314, 306, 305, 301, 300, 300, 301, 291, 307, 269, 302, 295, 283, 277  ]                     # events counted by A and C 
voltages  = [1298, 1325, 1350, 1399, 1425, 1455, 1502, 1525, 1555, 1601, 1623, 1649, 1701, 1725, 1755, 1803, 1825, 1852, 1899, 1928, 1949, 1999, 2022, 2054, 2101  ]     # voltages of B


# Efficiency as the ratio of N_ABC/N_AC

efficiency = []
for i in range(0, len(N_AC)):
    efficiency.append(N_ABC[i]/N_AC[i])

# Binomial errors 
errors = []
for i in range(0, len(efficiency)):
    errors.append(math.sqrt(efficiency[i]*(1-efficiency[i])/N_AC[i]))


# plot for the efficiencies using binomial statistics 

img1, ax1 = plt.subplots(figsize = [10,8])

plt.title('Efficiency vs voltages with binomial statistics')
plt.errorbar(voltages, efficiency, yerr = errors, color= 'blue' ,fmt='o', ecolor = 'green', markersize=4, capsize = 6)
plt.xlabel(r'Voltages (V)')
plt.ylabel(r'Efficiency ($\epsilon_B$)')
plt.axhline(y = 0 , c = 'red', linestyle  = '--')
plt.axhline(y = 1, c = 'red', linestyle  = '--')


ins = ax1.inset_axes([0.45, 0.3, 0.35,0.35])
ins.axhline(color='gray', linewidth=2)
ins.errorbar(voltages, efficiency, yerr = errors, color= 'blue' ,fmt='o', ecolor = 'green', markersize=4, capsize = 6)
ins.set_xlabel(r'Voltages(V)')
ins.set_ylabel(r'Efficiency ($\epsilon_B$)')
ins.set_xlim(1300,1450)
ins.set_ylim(0,0.05)


plt.show()


# Efficiency using de agostini method

N_ABC_agostini = []
N_AC_agostini = []

for (el1,el2) in zip(N_ABC, N_AC):
    N_ABC_agostini.append(el1+1)
    N_AC_agostini.append(el2+2)

efficencies_agostini = []
for i in range(0, len(N_AC)):
    efficencies_agostini.append(N_ABC_agostini[i]/N_AC_agostini[i])


# errors using de agostini method

errors_agostini = []

for (e,N) in  zip(efficencies_agostini, N_AC_agostini):
    error = math.sqrt((e*(1-e))/(N+3))
    errors_agostini.append(error)



# plot for the efficiencies with de agostini method 
img2, ax2 = plt.subplots(figsize = [10,8])

plt.title('Efficiency vs voltages with DeAgostini method')
plt.errorbar(voltages, efficencies_agostini, yerr = errors_agostini, color = 'red' ,fmt='o', ecolor = 'black', markersize = 2, capsize = 4)
plt.xlabel(r'Voltages (V)')
plt.ylabel(r'Efficiency ($\epsilon_B$)')
plt.axhline(y = 0 , c = 'red', linestyle  = '--')
plt.axhline(y = 1, c = 'red', linestyle  = '--')


ins = ax2.inset_axes([0.45, 0.3, 0.35,0.35])
ins.axhline(color='gray', linewidth=2)
ins.errorbar(voltages, efficencies_agostini, yerr = errors_agostini, color = 'red' ,fmt='o', ecolor = 'black', markersize = 2, capsize = 4)
ins.set_xlabel(r'Voltages(V)')
ins.set_ylabel(r'Efficiency ($\epsilon_B$)')
ins.set_xlim(1300,1450)
ins.set_ylim(0,0.05)
plt.show()


# plot on the same graph using binomial and de agostini method 

img, ax = plt.subplots(figsize = [10,8])

#plt.figure(figsize = [10,8])
plt.title('Efficiency vs voltages with the 2 methods')
plt.errorbar(voltages, efficencies_agostini, yerr = errors_agostini, color = 'red' ,fmt='o', ecolor = 'black', markersize = 4, capsize = 6, label = r'Method 2')
plt.errorbar(voltages, efficiency, yerr = errors, color= 'blue' ,fmt='o', ecolor = 'green', markersize = 4, capsize = 6, label = r'Binomial', alpha = 0.8)
plt.xlabel(r'Voltages (V)')
plt.ylabel(r'Efficiency ($\epsilon_B$)')
plt.axhline(y = 0 , c = 'red', linestyle  = '--')
plt.axhline(y = 1, c = 'red', linestyle  = '--')
plt.legend(loc = 'upper left', bbox_to_anchor=(0.01,0.8))



ins = ax.inset_axes([0.45, 0.3, 0.35,0.35])
ins.axhline(color='gray', linewidth=2)
ins.errorbar(voltages, efficencies_agostini, yerr = errors_agostini, color = 'red' ,fmt='o', ecolor = 'black', markersize = 4, capsize = 6, label = r'Method 2')
ins.errorbar(voltages, efficiency, yerr = errors, color= 'blue' ,fmt='o', ecolor = 'green', markersize = 4, capsize = 6, label = r'Binomial' )
ins.set_xlabel(r'Voltages(V)')
ins.set_ylabel(r'Efficiency ($\epsilon_B$)')
ins.set_xlim(1300,1450)
ins.set_ylim(0,0.05)
ins.legend(loc = 'upper left')

plt.show()


# define a test function to fit the data 

def test_func(x,A):
    """ tanh(x) as test function 
        - A :  represents the mean value, represents a translation """
    return 0.4*np.tanh(A*(x-1500))+0.4
# initial values for the params

np_efficiency = np.array(efficiency)
np_voltages   = np.array(voltages)
errors = np.array(errors)

np_dag_eff = np.array(efficencies_agostini)
errors_dag = np.array(errors_agostini)

pstart = 0.011
params, params_covariance = curve_fit(test_func, np_voltages, np_efficiency)
print('Params: ', params)
print('Params covariance: ', params_covariance)

plt.figure(figsize = [10,8])
plt.errorbar(voltages, efficiency, yerr = errors, color= 'blue' ,fmt='o', ecolor = 'green', markersize = 4, capsize = 6, label = r'Data' )
plt.plot(np_voltages, test_func(np_voltages, params), label = r'fit')
plt.legend(loc = 'upper left')
plt.show()



def test_erf(x, A, B, C):
    """ Test function as error function:
    - A : factor that squishes the function between 0 and 0.9
    - B : represents the mean value 
    - C : represents the sigma of the distribution 
    """
    return 0.5*A*(1+erf((x-B)/(math.sqrt(2)*C)))


pstart_erf = np.array([0.8, 1500, 50 ])
params_erf, params_covariance_erf  = curve_fit(test_erf, np_voltages, np_efficiency, p0 = pstart_erf)
print('Params: ', params_erf)
print('Params covariance: ', params_covariance_erf)


# fit with errorf function 
plt.figure(figsize = [10,8])
plt.title(r'Fit with error function')
plt.errorbar(voltages, efficiency, yerr = errors, color= 'blue' ,fmt='o', ecolor = 'green', markersize = 4, capsize = 6, label = r'Data' )
plt.plot(np_voltages, test_erf(np_voltages, params_erf[0], params_erf[1], params_erf[2]), label = r'Fit', c = 'blue')
plt.legend(loc = 'upper left')
plt.show()




















