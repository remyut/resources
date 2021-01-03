#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Dec 30 21:40:05 2020

@author: remy
"""

import folium
from decimal import Decimal
popupMsg= "Postcode "


file = open("list.txt", "r")
contents = file.read()
dictionary = eval(contents)
file.close()

m = folium.Map(location=[1.37057765782637, 103.857854578394], tiles='Stamen Toner',
                   zoom_start=13, control_scale=True)

outfp = "hdb_map.html"

for i in dictionary:
   msg = popupMsg + str(i)
   folium.Marker([dictionary[i][0], dictionary[i][1]], popup=msg).add_to(m)
   

folium.Circle([1.37057765782637, 103.857854578394],
                    radius=4000
                   ).add_to(m)



m.save(outfp)

