# 4-DOF Robotic Arm with Claw

This project documents the design and implementation of a **4-DOF robotic arm** capable of lifting payloads up to 500 g.  
It covers **mechanical design**, **electronics integration**, and **software development** on the ESP32 with simplified forward kinematics for wrist leveling.

---

## 📂 Project Structure
- **Mechanical/** – SolidWorks models, CAD renders
- **Electronics/** – Wiring diagrams, power setup notes
- **Software/** – ESP32 C++ code (PlatformIO, PCA9685 control)
- **Docs/** – Torque analysis, lessons learned, results
- **Images/** – Photos and testing screenshots

---

## ⚙️ Features
- Dual MG996R shoulder servos with torque sharing  
- Gear-driven claw with gripping lips for secure grasping  
- Wrist auto-leveling to keep claw parallel to the ground  
- Modular 3D-printed H-beam links for strength and low weight  
- Serial keyboard control interface (manual testing and debugging)

---

## 🔧 Hardware Setup
1. **Power**
   - 6×AA battery pack (~9 V) → PCA9685 `V+` and `GND` rails  
   - ESP32 `GND` tied to PCA9685 `GND` for common reference   

2. **Wiring**
   - Servos connected to PCA9685 channels:
     - Base = Channel 0  
     - Shoulder (Right + Left mirrored) = Channels 1 & 2 respectively 
     - Elbow = Channel 3  
     - Wrist = Channel 4  
     - Claw = Channel 5  
   - ESP32 connected to PCA9685 via I²C (`SDA = 21`, `SCL = 22`)  

3. **Assembly**
   - Mount servos into 3D-printed H-beam arms  
   - Use screws as seen in model 
   - Ensure claw gear teeth are aligned before powering up  

---

## 💻 Software Setup
   - Install [PlatformIO](https://platformio.org/) (recommended) or Arduino IDE.  

---

## 🎮 Controls

The robotic arm can be manually operated via **serial keyboard input**.  

| Key | Action             |
|-----|--------------------|
| `w` | Shoulder up        |
| `s` | Shoulder down      |
| `a` | Base rotate left   |
| `d` | Base rotate right  |
| `q` | Elbow up           |
| `e` | Elbow down         |
| `z` | Wrist up           |
| `c` | Wrist down         |
| `r` | Claw open          |
| `f` | Claw close         |
| `p` | Park pose (reset)  |

- The **Park pose** initializes all joints to a neutral, safe position.  
- The **wrist auto-leveling function** ensures the claw remains parallel to the ground whenever the shoulder or elbow moves.  
