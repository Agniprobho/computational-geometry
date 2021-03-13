#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Mar 12 11:14:18 2021

@author: agni
"""
import os
import numpy as np
import matplotlib.pyplot as plt
import imageio
import random

class Point():
    x=0
    y=0
    def __init__(self):
        self.x=0
        self.y=0
    def __eq__(self,other):
        return self.x==other.x and self.y==other.y
    
class Edge(Point):
    def __init__(self,a,b):
        self.a=Point()
        self.b=Point()
        self.a.x=0
        self.a.y=0
        self.b.x=0
        self.b.y=0    
        
        
class Triangle(Point):
    def __init__(self,a,b,c):
        self.a=Point()
        self.b=Point()
        self.c=Point()
        self.a.x=0
        self.a.y=0
        self.b.x=0
        self.b.y=0
        self.c.x=0
        self.c.y=0
    def __eq__(self,other):
        return self.a.x==other.a.x and self.a.y==other.a.y and self.b.x==other.b.x and self.b.y==other.b.y and self.c.x==other.c.x and self.c.y==other.c.y
        
def anima(points):  
    scale=0.1
    maxX=-1000
    minX=1000
    maxY=-1000
    minY=1000
    
    x_vals1 = []
    y_vals1 = []
    ptsX = []
    ptsY = []
    x1_vals = []
    y1_vals = []
    x_inter = []
    y_inter = []
    filenames = [] #store png sequence
    
    X = points[:,0]
    Y = points[:,1]
    (m,n) = points.shape
    
    for i in range(m):
        if X[i]>maxX:
            maxX=X[i]
        if X[i]<minX:
            minX=X[i]
        if Y[i]>maxY:
            maxY=Y[i]
        if Y[i]<minY:
            minY=Y[i]
            
    A = Point()
    B = Point()
    C = Point()
    D = Point()
    
    supT = Triangle(A,B,C)
    T = []
    
    def cP(A,B,C,D):
        a = A.x - D.x
        b = A.y - D.y
        c = (A.x*A.x - D.x*D.x) + (A.y * A.y - D.y * D.y)
        d = B.x - D.x
        e = B.y - D.y
        f = (B.x * B.x - D.x * D.x) + (B.y * B.y - D.y * D.y)
        g = C.x - D.x
        h = C.y - D.y
        i = (C.x * C.x - D.x * D.x) + (C.y * C.y - D.y * D.y)

        detD = a * (e * i - f * h) + b * (f * g - d * i) + c * (d * h - e * g)

        if detD>0:
            return True
        else:
            return False
    
    supT.a.x = maxX + ((maxX - minX) / 2) + scale
    supT.a.y = minY - scale
    
    supT.b.x = (maxX + minX) / 2
    supT.b.y = maxY - minY + maxY

    supT.c.x = (maxX + minX - supT.a.x)
    supT.c.y = supT.a.y
    
    T.append(supT)
    k=0
    for pt in range(m):        
        badT = []
        A.x = X[pt]
        A.y = Y[pt]
        for k in T:
            if cP(k.a, k.b, k.c, A)==True:         
                badT.append(k)
        
        ptsX.append(A.x)
        ptsY.append(A.y)
        
        Poly = []
        for tri in range(len(badT)):
            e1 = Edge(A,B)
            e2 = Edge(A,B)
            e3 = Edge(A,B)
            
            e1.a.x = badT[tri].a.x
            e1.b.x = badT[tri].b.x
            e2.a.x = badT[tri].b.x
            e2.b.x = badT[tri].c.x
            e3.a.x = badT[tri].c.x
            e3.b.x = badT[tri].a.x
            e1.a.y = badT[tri].a.y
            e1.b.y = badT[tri].b.y
            e2.a.y = badT[tri].b.y
            e2.b.y = badT[tri].c.y
            e3.a.y = badT[tri].c.y
            e3.b.y = badT[tri].a.y
            
            if len(badT)==1:
                Poly.append(e1)
                Poly.append(e2)
                Poly.append(e3)
                
            for tri1 in range(tri+1,len(badT)):
                e4 = Edge(A,B)
                e5 = Edge(A,B)
                e6 = Edge(A,B)
                
                e4.a.x = badT[tri1].a.x
                e4.b.x = badT[tri1].b.x
                e5.a.x = badT[tri1].b.x
                e5.b.x = badT[tri1].c.x
                e6.a.x = badT[tri1].c.x
                e6.b.x = badT[tri1].a.x
                e4.a.y = badT[tri1].a.y
                e4.b.y = badT[tri1].b.y
                e5.a.y = badT[tri1].b.y
                e5.b.y = badT[tri1].c.y
                e6.a.y = badT[tri1].c.y
                e6.b.y = badT[tri1].a.y
                
                if not((e1.a==e4.b and e1.b==e4.a) or (e1.a==e5.b and e1.b==e5.a) or (e1.a==e6.b and e1.b==e6.a)):
                    Poly.append(e1)
                
                if not((e2.a==e4.b and e2.b==e4.a) or (e2.a==e5.b and e2.b==e5.a) or (e2.a==e6.b and e2.b==e6.a)):
                    Poly.append(e2)
                    
                if not((e3.a==e4.b and e3.b==e4.a) or (e3.a==e5.b and e3.b==e5.a) or (e3.a==e6.b and e3.b==e6.a)):
                    Poly.append(e3)
                    
                if not((e4.a==e1.b and e4.b==e1.a) or (e4.a==e2.b and e4.b==e2.a) or (e4.a==e3.b and e4.b==e3.a)):
                    Poly.append(e4)
                    
                if not((e5.a==e1.b and e5.b==e1.a) or (e5.a==e2.b and e5.b==e2.a) or (e5.a==e3.b and e5.b==e3.a)):
                    Poly.append(e5)
                    
                if not((e6.a==e1.b and e6.b==e1.a) or (e6.a==e2.b and e6.b==e2.a) or (e6.a==e3.b and e6.b==e3.a)):
                    Poly.append(e6)
        
        for tri in badT:
            T.remove(tri)
        
        for edg in Poly:
            T_1 = Triangle(A,B,C)
            T_1.a.x = edg.a.x
            T_1.b.x = edg.b.x
            T_1.c.x = A.x
            T_1.a.y = edg.a.y
            T_1.b.y = edg.b.y
            T_1.c.y = A.y            
            T.append(T_1)
        
        for tri in T:
            plt.scatter(ptsX,ptsY)
            x1_vals = [tri.a.x, tri.b.x, tri.c.x, tri.a.x]
            y1_vals = [tri.a.y, tri.b.y, tri.c.y, tri.a.y]
            plt.plot(x1_vals,y1_vals,'-y')
            if not(tri.a == supT.a or tri.b == supT.a or tri.a == supT.b or tri.b == supT.b or tri.a == supT.c or tri.b == supT.c):
                x_inter = [tri.a.x, tri.b.x]
                y_inter = [tri.a.y, tri.b.y]
                plt.plot(x_inter,y_inter,'-g')
            if not(tri.b == supT.a or tri.c == supT.a or tri.b == supT.b or tri.c == supT.b or tri.b == supT.c or tri.c == supT.c):
                x_inter = [tri.b.x, tri.c.x]
                y_inter = [tri.b.y, tri.c.y]
                plt.plot(x_inter,y_inter,'-g')
            if not(tri.a == supT.a or tri.c == supT.a or tri.a == supT.b or tri.c == supT.b or tri.a == supT.c or tri.c == supT.c):
                x_inter = [tri.c.x, tri.a.x]
                y_inter = [tri.c.y, tri.a.y]
                plt.plot(x_inter,y_inter,'-g')
        
        plt.xlim(-0.5,1.8)
        plt.ylim(-0.1,2) 
        #create filename and append to list
        r1=random.randint(0,100000)
        filename = f'{r1}.png'
        filenames.append(filename)
        plt.savefig(filename)
        plt.pause(0.5)
        plt.cla()
            
    TR=[]             
    for tri in T:
        if not(tri.a == supT.a or tri.b == supT.a or tri.c == supT.a or tri.a == supT.b or tri.b == supT.b or tri.c == supT.b or tri.a == supT.c or tri.b == supT.c or tri.c == supT.c):
            TR.append(tri)
            
    print(len(TR))
    plt.scatter(ptsX,ptsY)
    for tri in TR:
        x_vals1 = [tri.a.x, tri.b.x, tri.c.x, tri.a.x]
        y_vals1 = [tri.a.y, tri.b.y, tri.c.y, tri.a.y]
        plt.plot(x_vals1,y_vals1,'-b')
    
    plt.xlim(-0.5,1.8)
    plt.ylim(-0.1,2)
    #create filename and append to list
    r1=random.randint(0,100000)
    filename = f'{r1}.png'
    filenames.append(filename)
    plt.savefig(filename)    
    plt.pause(0.5)
        
    #build gif
    with imageio.get_writer('delaunay.gif',mode='I') as writer:
        for filename in filenames:
            image=imageio.imread(filename)
            writer.append_data(image)
    
    #remove files
    for filename in set(filenames):
        os.remove(filename)
          
points = np.array([[0.5,0.2], [0.3,0.6], [0.8,0.8], [0.1,0.9], [0.9,0.1],[0.6,0.5],[0.7,0.4]])
anima(points) 
plt.xlim(-0.5,1.8)
plt.ylim(-0.1,2) 
plt.show()

