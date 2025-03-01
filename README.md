# 📌 Philosophers - Dining Philosophers Problem

A solution to the **Dining Philosophers Problem**, implemented as part of the **42 school curriculum**. This project is designed to explore **multithreading, process synchronization, and concurrency issues** in C using **pthread, mutexes, and semaphores**.

---

## 🚀 Features
- **Multiple Philosophers**: Each philosopher alternates between thinking, eating, and sleeping.
- **Thread Synchronization**: Uses **pthread mutexes** and **semaphores** to prevent deadlocks.
- **Avoids Deadlock & Race Conditions**: Ensures no two adjacent philosophers eat at the same time.
- **Performance Optimization**: Efficient resource sharing without unnecessary waiting.

---

## 🛠️ Tech Stack
| Category       | Technologies Used |
|---------------|------------------|
| **Language**  | C |
| **Threading** | pthreads |
| **Sync Tools**| Mutexes, Semaphores |

---

## 📝 Installation & Setup
### 📂 1️⃣ Clone the Repository
```sh
git clone https://github.com/karagoz36/philosophers.git
cd philosophers
```

### 🔧 2️⃣ Build the Project
```sh
make
```

### 🎮 3️⃣ Run the Program
```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

#### Example:
```sh
./philo 5 800 200 200
```
This runs the simulation with **5 philosophers**, each having **800ms** before dying if they don’t eat, **200ms** to eat, and **200ms** to sleep.

---

## 📈 Program Behavior
- Each **philosopher** tries to pick up two forks (mutexes).
- They **eat** for a defined period, then release the forks.
- If a philosopher doesn’t eat within `time_to_die`, the simulation stops.

---

## 📊 Example Output
```
0 1 has taken a fork
0 2 has taken a fork
0 1 is eating
0 2 is eating
```

---

## 💡 Notes
- **If only one philosopher is present, they will starve** (as they cannot pick up two forks).
- **No data races occur** due to mutex synchronization.
- **Ensure system supports pthreads** before compiling.

---

