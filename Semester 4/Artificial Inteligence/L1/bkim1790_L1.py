#Nev:Bauer Kristof
#Csoport 521
#Lab1

import math
import heapq
from matplotlib import cm, pyplot, pyplot as plt
from mpl_toolkits.mplot3d.axes3d import Axes3D
import numpy as np

fig = plt.figure()
ax = Axes3D(fig)
points = [] #A surface pointok
startPoints=[] #A kiindulo x,y,z koordinatak
startPos=-1 #StartIndex
endPos=-1 #EndIndex

class PriorityQueue: #Sajat queue
    def __init__(self):
        self.elements = []
    
    def empty(self):
        return len(self.elements) == 0
    
    def put(self, item, priority):
        heapq.heappush(self.elements, (priority, item))
    
    def get(self):
        return heapq.heappop(self.elements)[1]

class Surface: #pontok classe
    def __init__(self, x, y,z,b):
        self.x = x
        self.y = y
        self.z=z
        self.b=b


def readPoints():
    z=[]
    pf = open("C:\\Users\\Kristof\\Documents\\points.txt") #beolvas startpointok
    for i, line in enumerate(pf):
        if i == 0:
            (sX,sY,sZ)=line.split()
            startPoints.append(Surface(sX,sY,sZ,-1))
        elif i == 1:
            (eX,eY,eZ)=line.split()
            startPoints.append(Surface(eX,eY,eZ,-1))

    
    f = open("C:\\Users\\Kristof\\Documents\\surface.txt") #beolvas surfacepointok
    i=0
    for line in f:
        (X, Y, Z, B) = line.split()
        z.append(float(Z))
        if (X==startPoints[0].x) and (Y==startPoints[0].y) and (Z==startPoints[0].z):
            startPos=i
           # print("STARTPOS Beolvas= ",startPos)
        if (X==startPoints[1].x) and (Y==startPoints[1].y) and (Z==startPoints[1].z):
            endPos=i
        points.append(Surface(X,Y,Z,int(B)))
        i+=1
    return startPos,endPos,z
   # print((startPos,endPos))


def neighbors(index): #szomszed kereses
    neigbors=[]
    topIndex=(((index+1)>=1) and ((index+1)<=250) )
    rightIndex = ((index+1) % 250 == 0)
    bottomIndex = (((index+1) >= 62250) and ((index+1)<=62500))
    leftIndex=((index+1) % 250 == 1)

    if(topIndex):
        if((index+1)==1): #ha bal felso sarok
            neigbors.append(index+1)
            neigbors.append(index+250+1)
            neigbors.append(index+250)
            return neigbors
        elif((index+1)==250): #jobb felso
            neigbors.append(index-1)
            neigbors.append(index+250)
            neigbors.append(index+250-1)
            return neigbors
        else: #ha csak siman fenti sorban van
            neigbors.append(index+1)
            neigbors.append(index-1)
            neigbors.append(index+250+1)
            neigbors.append(index+250-1)
            neigbors.append(index+250)
            return neigbors
    elif(rightIndex): #ha a jobboldali oszlopban van
        neigbors.append(index-1)
        neigbors.append(index-250)
        neigbors.append(index-250-1)
        neigbors.append(index+250)
        neigbors.append(index+250-1)
        return neigbors
    
    elif(bottomIndex):
        if((index+1)==62500): #jobb also
            neigbors.append(index-250)
            neigbors.append(index-250-1)
            neigbors.append(index-1)
            return neigbors
        elif((index+1)==62250): #bal also
            neigbors.append(index+1)
            neigbors.append(index-250)
            neigbors.append(index-250+1)
            return neigbors
        else:
            neigbors.append(index-1)
            neigbors.append(index+1)
            neigbors.append(index-250)
            neigbors.append(index-250+1)
            neigbors.append(index-250-1)
            return neigbors
    elif(leftIndex):
        neigbors.append(index+1)
        neigbors.append(index-250)
        neigbors.append(index-250+1)
        neigbors.append(index+250)
        neigbors.append(index+250+1)
        return neigbors
    else: #valahol random 8 szomszedos
        neigbors.append(index-250)
        neigbors.append(index+250)
        neigbors.append(index-1)    
        neigbors.append(index+1)
        neigbors.append(index-250-1)
        neigbors.append(index-250+1)
        neigbors.append(index+250+1)
        neigbors.append(index+250-1)
        return neigbors


def heuristic(a, b): #euklideszi tavolasag
    d = math.sqrt((float(points[b].x) - float(points[a].x)) ** 2 + (float(points[b].y) - float(points[a].y)) ** 2 + (float(points[b].z) - float(points[a].z)) ** 2)  
    return d

def lepesCost(a,b): #lepes heurisztika
    return 1

def energyCost(a, b): #energia heurisztika
    if points[b].z < points[a].z:
        return 0
    else:
        return (float(points[b].z) - float(points[a].z))


def AStar(start,end,cost):
    frontier = PriorityQueue()
    frontier.put(start, 0) #index,priority paros
    came_from = {}
    cost_so_far = {}
    came_from[start] = None
    cost_so_far[start] = 0
    
    while not frontier.empty():
        current = frontier.get()
    
        if current == end:
            break
        
        for next in neighbors(current):
            if(points[next].b == 0):
                new_cost = cost_so_far[current] +cost(current,next)
            
                if next not in cost_so_far or new_cost < cost_so_far[next]:
                    cost_so_far[next] = new_cost
                    priority = new_cost + heuristic(next, end)
                    frontier.put(next, priority)
                    came_from[next] = current
            
    return came_from, cost_so_far[end]

def AStar2(start,end,cost):
    frontier = PriorityQueue()
    frontier.put(start, 0) #index,priority paros
    came_from = {}
    cost_so_far = {}
    came_from[start] = None
    cost_so_far[start] = 0


    while not frontier.empty():
        current = frontier.get()
    
        if current == end:
            break
        
        for next in neighbors(current):
            #print(neighbors(current),"---",next)
            if(points[next].b == 0):
                new_cost = cost_so_far[current] +cost(current,next)
            
                if next not in cost_so_far or new_cost < cost_so_far[next]:
                    cost_so_far[next] = new_cost
                    priority = new_cost + energyCost(next, end)
                    frontier.put(next, priority)
                    came_from[next] = current
            
    return came_from, cost_so_far[end]




def reconstruct_path(came_from, start, goal):
    current = goal
    path = []
    while current != start:
        path.append(current)
        current = came_from[current]
    path.append(start)
    path.reverse()
    return path
    

def main():
    startPos,endPos,z=readPoints()


    xs = list(range(263, 250 + 263))
    ys = list(range(132, 250 + 132))
    xs, ys = np.meshgrid(xs, ys)
    zs = np.array(z).reshape(250, 250)
    surf = ax.plot_surface(xs, ys, zs, cmap = cm.jet, edgecolors = 'k', linewidth = 0.01, antialiased = False, alpha = 0.5)
    fig.colorbar(surf, shrink=0.5, aspect=5)
   
    print("Lepes Szamolas")
    came_from, cost_so_far = AStar(startPos,endPos,lepesCost)
    path=reconstruct_path(came_from,startPos,endPos)
    print("Utvonal= ",path)
    print("Lepeszam= ",len(path)-1)
    print("Tavolsag = ",cost_so_far)

    print("\n")
    print("Tavolsag szamolas")
    came_fromdist, cost_so_fardist = AStar(startPos,endPos,heuristic)
    pathdist=reconstruct_path(came_fromdist,startPos,endPos)
    print("Utvonal= ",pathdist)
    print("Lepeszam= ",len(pathdist)-1)
    print("Tavolsag = ",cost_so_fardist)

    print("\n")
    print("Energia szamolas")
    newpath, energy = AStar2(startPos,endPos,energyCost)
    npath=reconstruct_path(newpath,startPos,endPos)
    print("Utvonal= ",npath)
    print("Lepeszam= ",len(npath)-1)
    print("Energy = ",energy)

    for i in path:
        ax.plot3D([float(points[i].x)], [float(points[i].y)], [float(points[i].z)], color = 'black', marker = '.')

    for i in pathdist:
        ax.plot3D([float(points[i].x)], [float(points[i].y)], [float(points[i].z)], color = 'blue', marker = '.')


    for i in npath:
            ax.plot3D([float(points[i].x)], [float(points[i].y)], [float(points[i].z)], color = 'red', marker = '.')
    plt.show()


main()