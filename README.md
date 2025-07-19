# Green Wave Traffic Simulation with OMNeT++

This project simulates a one-way road traffic scenario, based on a configurable model of traffic lights and vehicle behavior. The goal is to analyze the impact of **traffic light synchronization (green wave)** and traffic flow under varying conditions.

---

##  Problem Description

A **one-way road** of length **L meters** contains **X intersections**, each regulated by a **traffic light**. These lights are placed at regular intervals (`D = L / X`) and alternate between **green** and **red** phases with a configurable **period P**.

The lights are synchronized to create a **"green wave"**: a vehicle traveling at **30 km/h**, starting on a green light at the first intersection, should encounter green lights at all subsequent intersections.

---

##  Vehicle Behavior

- Vehicles arrive on the road at **random intervals**, defined by an **exponential distribution** with parameter **T**.
- If a vehicle reaches an intersection while the light is green and no vehicle is queued, it proceeds.
- Otherwise, the vehicle **queues up**.
- When the light turns green, only **one vehicle at a time** can pass, taking a constant time **C**.

---

##  Objectives

The simulation evaluates:

- The **total travel time** for a vehicle along the road.
- How travel time is affected by different values of:
  - Number of intersections (**X**)
  - Light period (**P**)
  - Vehicle speed (**V**)

---

## Tools and Techiniques

This project utilizes a simulation-based approach
 to model the system by using Omnet++. This tool, that stands for Objective Modu
lar Network Testbed in C++, is an open-source, extensible, and modular simulation
 platform designed for researchers and developers to simulate complex systems. It
 uses a component-based architecture. Systems are modeled as hierarchies of mod
ules (simpleorcompound)thatcommunicatethroughmessage-passing. Thebehav
ior of modules is implemented in C++, while the network topology and connections
 are described using the Network Description (NED) language.

---

##  Scenarios Evaluated

1. **Constant speed**:
   - All vehicles travel at a fixed speed (e.g., 30 km/h or 8.33 m/s).
2. **Variable speed**:
   - Vehicles travel at a speed **V**, drawn from a **uniform distribution**:  
     `V ~ U(4 m/s, 12 m/s)`

---

##  Experiment Design: 2³ Factorial Analysis

To evaluate how different parameters affect vehicle travel time, we apply a **2³ factorial design** to both the **constant speed** and **variable speed** scenarios. The three independent factors are:

- **P**: Traffic light period  
- **X**: Number of intersections  
- **L**: Road length

Each factor has two levels:

| Factor | Low Level | High Level |
|--------|-----------|------------|
| **L**  | 400 m     | 700 m      |
| **X**  | 2         | 5          |
| **P**  | 40 s      | 80 s       |

Each combination of parameters corresponds to one of the 8 runs:

| Run | P Level | X Level | L Level | Combination          |
|-----|---------|---------|---------|----------------------|
| 1   | Low     | Low     | Low     | (−1, −1, −1)         |
| 2   | Low     | Low     | High    | (−1, −1, +1)         |
| 3   | Low     | High    | Low     | (−1, +1, −1)         |
| 4   | Low     | High    | High    | (−1, +1, +1)         |
| 5   | High    | Low     | Low     | (+1, −1, −1)         |
| 6   | High    | Low     | High    | (+1, −1, +1)         |
| 7   | High    | High    | Low     | (+1, +1, −1)         |
| 8   | High    | High    | High    | (+1, +1, +1)         |

---

### 🧾 Evaluation Conditions

Each experiment was **repeated 30 times** to ensure statistical significance. The system was evaluated under the following conditions:

#### 1. Speed Modes
- **Constant Speed:** All vehicles move at 30 km/h (8.33 m/s).
- **Variable Speed:** Vehicle speed is sampled from a uniform distribution: `V ~ U(4 m/s, 12 m/s)`.

#### 2. Traffic Density
- **Crowded Scenario:** Vehicles arrive every **30 seconds** on average.
- **Not Crowded Scenario:** Vehicles arrive every **60 seconds** on average.

A **95% confidence interval (CI)** is used for all estimated metrics.

---

##  Metrics Collected

- **Average Travel Time:** The total time a vehicle takes from entering the road to exiting.
- **Average Waiting Time:** Time spent queued at red lights or behind other vehicles.
- **Green Wave Ratio:** Number of vehicles facing a green wave over the total who travers the whole road.

---

