# 🌄 Catan Game

A Java-based version of the classic board game **The Settlers of Catan**, designed for **3 players**.  
The project demonstrates **Object-Oriented Programming**, **resource management**, and **strategic gameplay logic**.

---

## 🎯 Game Overview
Each player competes to reach **10 victory points** by building **roads**, **settlements**, and **cities**,  
while managing resources and trading strategically with others.

The board consists of **19 hexagonal tiles**, each producing a specific resource:  
🌲 Wood | 🧱 Brick | 🌾 Grain | 🐑 Wool | ⛰️ Ore | 🏜️ Desert (none)

---

## 🧩 Main Mechanics
- 🎲 **Dice rolls** determine which tiles produce resources each turn.  
- 💱 **Trading system** between players or with the bank.  
- 🏗️ **Building** roads, settlements, and cities using resource combinations.  
- 🎴 **Development cards** grant special abilities or victory points.  
- 🧮 First player to **reach 10 points** wins the game.

---

## 🧱 Project Structure (OOP Design)

| Class | Description |
|--------|-------------|
| **Catan** | Main game controller managing players, board, and cards. |
| **Board** | Holds all tiles and manages the layout. |
| **Hexagon** | Represents a land tile (terrain type, number, edges, vertices). |
| **Player** | Manages player name, resources, roads, settlements, points. |
| **Card** | Abstract base class for development cards. |
| **DevelopmentCard** | Subclasses implement specific effects (Monopoly, Road Building, etc.). |

---

## 🧠 Concepts Demonstrated
- Object-Oriented Design (Encapsulation, Inheritance, Polymorphism)  
- Game state management and turn logic  
- Data modeling of resources and entities  
- Extensible architecture for future rule additions  

 ## Game Board

![image](https://github.com/oriyaPerel/Catan_Exe3/assets/159001341/600c9244-8009-402d-a7d0-03013fc0ec77)


