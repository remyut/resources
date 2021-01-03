#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Sat Dec 12 14:18:39 2020

@author: remy
"""
#https://developers.onemap.sg/commonapi/staticmap/getStaticImage?layerchosen=default&postal=228598&zoom=13&height=512&width=512&polygons=[[1.31955,103.84223],[1.31755,103.84223],[1.31755,103.82223],[1.31755,103.81223],[1.31955,103.84223]]:255,255,105&points=[1.31955,103.84223,%22255,255,178%22,%22B%22]|[1.31801,103.84224,%22175,50,0%22,%22A%22]
#https://developers.onemap.sg/commonapi/staticmap/getStaticImage?layerchosen=default&lat=1.37057765782637&lng=103.857854578394&zoom=13&height=512&width=512&points=[1.37057765782637,103.857854578394,%22255,%20255,%20178%22,%20%22A%22]|[1.3709981067467165,103.85785639187644,%22255,%20255,%20178%22,%20%22A%22]|[1.3716257020332439,103.85773610752673,%22255,%20255,%20178%22,%20%22A%22]|[1.37203236308666,103.85762537579666,%22255,%20255,%20178%22,%20%22A%22]|[1.3728200084432443,103.8577840263619,%22255,%20255,%20178%22,%20%22A%22]|[1.3731647858275278,103.8574118308379,%22255,%20255,%20178%22,%20%22A%22]|[1.3729137631119295,103.85704609864007,%22255,%20255,%20178%22,%20%22A%22]

import math, sys, io, numpy as np
from matplotlib import pyplot as plt
from decimal import Decimal
from onemapsg import OneMapClient
import PIL.Image as Image
sys.path.append(".")
from Point import point
from LocationContainer import locationContainer
import folium

client = OneMapClient("email", "password")
client.get_token(email=None, password=None)
client.check_expired_and_refresh_token()



def convertSVY21ToWSG84(coordinates):
    return client.SVY21_to_WGS84(coordinates)

def drawPerimeter(polygon):
   wsg84Polygon = []
   for i in polygon:
       wsg84Polygon.append(convertSVY21ToWSG84(i))   
       
   polygons = "["
   
   lastItem = len(wsg84Polygon) - 1
       
   for i, (key, value) in enumerate(wsg84Polygon):
        polygons += "[" + str(wsg84Polygon[i][key]) + "," + str(wsg84Polygon[i][value]) +"]"
        
        if(i < lastItem):
            polygons += ","
                    
   polygons += "]"
   polygons += ":255, 105, 105"
 
   return polygons
   
def generateBaseMatrix(initPoint):
   
    matrix = []
   
    for i in np.arange(initPoint.getY(),initPoint.getY() + 4000.0, 200.0):
            for j in np.arange(initPoint.getX(), initPoint.getX() - 4000.0, -200.0):
                arr = [j, i]
                matrix.append(arr)
                
    for i in np.arange(initPoint.getY(), initPoint.getY() + 4000.0, 200.0):
            for j in np.arange(initPoint.getX(), initPoint.getX() + 4000.0,  200.0):
                 arr = [j, i]
                 matrix.append(arr)
                
    for i in np.arange(initPoint.getY(), initPoint.getY() - 4000.0, -200.0):
            for j in np.arange(initPoint.getX(), initPoint.getX() - 4000.0,  -200.0):
                 arr = [j, i]
                 matrix.append(arr)
                
    for i in np.arange(initPoint.getY(), initPoint.getY() - 4000.0, -200.0):
            for j in np.arange(initPoint.getX(), initPoint.getX() + 4000.0,  200.0):
                 arr = [j, i]
                 matrix.append(arr)
                
 
        
    data = np.array(matrix)
    #print(data)
    #print(len(data))
    x, y = data.T
    
    plt.scatter(x,y)
  
    plt.scatter(x[1599],y[1599], c='coral') #3
    plt.scatter(x[19],y[1599], c='coral') #4
    plt.scatter(x[19],y[799], c='coral') #1
    plt.scatter(x[1599],y[799], c='coral') #2
    plt.show()
    
    polygon = [(x[19],y[799]), (x[1599],y[799]), (x[1599],y[1599]), (x[19],y[1599]), (x[19],y[799]) ]
    return polygon, matrix

    #print(matrix)

def findDistance(toAdd, x, y):
    xx = x +toAdd
    yy = y + toAdd
    
    
def converSVY21ToWSG84(x, y):
    client.EPSG_to_WGS84

def generateMap(polygons=None, points=None):
            
    initloc = [1.37057765782637, 103.857854578394]
    #png_map = client.generate_static_map("default", location=initloc, zoom=14, width=512, height=512, polygons=polygons, lines=None, points=points, color=None, fill_color=None)
    #image = Image.open(io.BytesIO(png_map))
    #image.save("out.png")
        
        

def distance__(initLocation, currentLocation):
         return math.sqrt((initLocation.getX() - currentLocation.getX()) ** 2 + (initLocation.getY()
                           - currentLocation.getY()) ** 2)
         
         
def distance(initLocation, currentLocation):
         return math.sqrt((initLocation.point.getX() - currentLocation.point.getX()) ** 2 + (initLocation.point.getY()
                           - currentLocation.point.getY()) ** 2)
         
def getResidences(listOfLocation, initLocation, coordinateMaxtrix):
    
    for i in coordinateMaxtrix:
        print ("discovering near " + str(i))
        ret = client.reverse_geocode_SVY21(i, buffer=200, address_type="HDB", other_features=False)
        for j in ret['GeocodeInfo']:
            loc = locationContainer()
            loc.setLocation(j)
            if(distance(initLocation, loc) <= 4000.0):
                 if(loc.getPostalCode() not in listOfLocation):
                     listOfLocation[loc.getPostalCode()] = loc.getWGS84Coordinates()
                     loc.printLocation()      
            else:
                print (" distance to far > 4km")
                     
                
            


         
def getFrom(listOfLocation, initLocation, currentLocation):
    if(distance(initLocation, currentLocation) > 4000.0):
        print ("RETURN distance to far > 4km")
        return
    else:
        print ("Keep discovering")
        listOfLocation[currentLocation.getPostalCode()] = currentLocation.getWGS84Coordinates()
        ret = client.reverse_geocode_SVY21(currentLocation.point.getSVY21Coordinates(), buffer=500, address_type="HDB", other_features=False)
        for i in ret['GeocodeInfo']:
            loc = locationContainer()
            loc.setLocation(i)
            if(loc.getPostalCode() == currentLocation.getPostalCode()):
                print("skip")
            else:
                if(loc.getPostalCode() not in listOfLocation):
                    loc.printLocation()
                    getFrom(listOfLocation, initLocation, loc)
           
        print("FINISH")

      

def main():
    listOfAllLocation = {}
    y = client.search(560561)
    initLoc = locationContainer()
    initLoc.setInitLocation(y["results"][0])
    initLoc.printLocation()
    #getFrom(listOfAllLocation, initLoc, initLoc)
    #print("DONE")
    #print(listOfAllLocation)
    initPoint = point(30730.5588699877, 39177.0434600972)
    polygon, coordinateMatrix = generateBaseMatrix(initPoint)
    getResidences(listOfAllLocation, initLoc, coordinateMatrix)
    print(listOfAllLocation)
    #poly = drawPerimeter(polygon)
    #print(poly)
    
    #generateMap(polygons=None, points=None)
    
if __name__ == "__main__":
    main()
