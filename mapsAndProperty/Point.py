#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Dec 20 21:04:51 2020

@author: remy
"""
#Lat = Y Long = X

class point():
    
     def __init__(self, x=0, y=0):
         self.x = x
         self.y = y
         self.lat = 0
         self.long = 0
         self.SVY21Coordinates=[self.x, self.y]
         self.WGS84Coordinates=[self.lat, self.long]
       
    
     def getX(self):
         return self.x
     
     def getY(self):
         return self.y
     
     def getLat(self):
         return self.lat
     
     def getLong(self):
         return self.long
     
     def getSVY21Coordinates(self):
         return self.SVY21Coordinates
     
     def getWGS84Coordinates(self):
         return self.WGS84Coordinates
     
     def setSVY21Coordinates(self, x, y):
         self.x = x
         self.y = y
         self.SVY21Coordinates=[self.x, self.y]
         
     def setWGS84Coordinates(self, lat, long):
         self.lat = lat
         self.long = long
         self.WGS84Coordinates=[self.lat, self.long]
        
         
    
         
         

         