#!/bin/sh

mkdir -p export/ardburno
cd export

function package() {
  cp ardburno.$1.gbr ardburno/ardburno.$2
}

package topsilk 1.gto    # GTO   Top Silkscreen (text)
package topmask 2.gts    # GTS   Top Soldermask (the 'green' stuff)
package top 3.gtl        # GTL   Top Copper (conducting layer)
package group1 4.gbl     # GBL   Bottom Copper
package bottommask 5.gbs # GBS   Bottom Soldermask
package outline 6.gml    # GML/GKO/GBR*  Board Outline*
# GBO   Bottom Silkscreen

# TXT   Routing and Drill (the holes and slots)
cp ardburno.plated-drill.cnc ardburno/ardburno.0.txt

zip -j ardburno/ardburno ardburno/*
