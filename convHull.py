# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import os
import numpy as np
import matplotlib.pyplot as plt
import imageio

def anima(points):  
    sorted_pts = points[np.argsort(points[:,0])]
    X = sorted_pts[:,0]
    Y = sorted_pts[:,1]
    (m,n) = points.shape
    x_vals = []
    y_vals = []
    x_vals1 = []
    y_vals1 = []
    filenames = [] #store png sequence
    
    CH = []
    
    leftMost = 0
    hullPoint = leftMost
    endPoint = -1
    
    k=0
    
    while endPoint!=leftMost:
        CH = np.append(CH,hullPoint)
        endPoint = 0
        for j in range(m):
            x_vals = [X[hullPoint],X[j]]
            y_vals = [Y[hullPoint],Y[j]]
            
            a = X[endPoint]
            b = Y[endPoint]
            c = X[j]
            d = Y[j]
            e = X[hullPoint]
            f = Y[hullPoint]
            arr1 = np.array([a-e,b-f,0])
            arr2 = np.array([c-e,d-f,0])
            
            #plt.cla()
            plt.plot(X,Y,'go')
            ln,=plt.plot(x_vals,y_vals,'-y')
            
            #create filename and append to list
            filename = f'{k}.png'
            filenames.append(filename)
            plt.savefig(filename)
            
            plt.pause(0.1)
            #remove current line
            ln.remove()
            
            cp = np.cross(arr1,arr2)
            if cp[2]>0 or endPoint==hullPoint:
                endPoint=j
                
            k = k+1
        
        #plt.cla()
        x_vals1.append(X[hullPoint])
        x_vals1.append(X[endPoint])
        y_vals1.append(Y[hullPoint])
        y_vals1.append(Y[endPoint])
        plt.plot(x_vals1,y_vals1,'-b')
        
        #create filename and append to list
        filename = f'{k}.png'
        filenames.append(filename)
        plt.savefig(filename)
        k=k+1
         
        hullPoint=endPoint
        
    plt.pause(0.5)
    
    #create filename and append to list
    filename = f'{k}.png'
    filenames.append(filename)
    plt.savefig(filename)
    
    #build gif
    with imageio.get_writer('convHull.gif',mode='I') as writer:
        for filename in filenames:
            image=imageio.imread(filename)
            writer.append_data(image)
    
    #remove files
    for filename in set(filenames):
        os.remove(filename)


points = np.random.rand(20,2)
anima(points)  
plt.tight_layout()
plt.show()