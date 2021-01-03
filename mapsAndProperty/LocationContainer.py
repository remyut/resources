#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Dec 21 00:04:58 2020

@author: remy
"""
import sys
from decimal import Decimal
sys.path.append(".")
from Point import point

class locationContainer():
    
    point = point()
        
    def setLocation(self, location_json):
        self.blk_no = location_json["BLOCK"]
        self.road_name = location_json["ROAD"]
        self.building = location_json["BUILDINGNAME"]
        self.address = "<undefined>"
        self.postal = location_json["POSTALCODE"]
        x = Decimal(location_json["XCOORD"])
        y = Decimal(location_json["YCOORD"])
        lat = Decimal(location_json["LATITUDE"])
        long = Decimal(location_json["LONGITUDE"])
        self.point.setWGS84Coordinates(lat, long)
        self.point.setSVY21Coordinates(x, y)
        
        if(self.blk_no == 'null'):
            self.blk_no = "<undefined>"
            
        if(self.road_name == 'null'):
            self.road_name = "<undefined>"
            
        if(self.building == 'null'):
             self.building = "<undefined>"
                            
        
    def setInitLocation(self, location_json):
        self.blk_no = location_json["BLK_NO"]
        self.road_name = location_json["ROAD_NAME"]
        self.building = location_json["BUILDING"]
        self.address = location_json["ADDRESS"]
        self.postal = location_json["POSTAL"]
        x = Decimal(location_json["X"])
        y = Decimal(location_json["Y"])
        lat = Decimal(location_json["LATITUDE"])
        long = Decimal(location_json["LONGITUDE"])
        self.point.setWGS84Coordinates(lat, long)
        self.point.setSVY21Coordinates(x, y)
       
          
        if(self.blk_no == 'null'):
            self.blk_no = "<undefined>"
            
        if(self.road_name == 'null'):
            self.road_name = "<undefined>"
            
        if(self.building == 'null'):
             self.building = "<undefined>"
        
    def getSVY21Coordinates(self):
        return self.point.getSVY21Coordinates()
    
    def getWGS84Coordinates(self):
        return self.point.getWGS84Coordinates()

    
    def getBlockNo(self):
        return self.blk_no;
    
    def getPostalCode(self):
        return self.postal 
    
    def printLocation(self):
         print("###Print location###")
         print(self.blk_no)
         print(self.road_name)
         print(self.building) 
         print(self.address) 
         print(self.postal)
         print(self.point.getSVY21Coordinates())
         print(self.point.getWGS84Coordinates())
         print("###Print location end###")
