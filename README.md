# C++ Pistache CRUD Service with PostgreSQL

## Overview
This project is a high-performance C++ CRUD REST API using the **Pistache** framework, integrated with **PostgreSQL** as the database. The service runs inside a **Docker container** and is configured to automatically create necessary tables on startup.

## Features
- REST API for CRUD operations on users.
- PostgreSQL database integration with **libpqxx**.
- Dockerized environment using `docker-compose`.
- Automatically creates tables on startup.

## Setup & Installation

### Prerequisites
Ensure you have the following installed:
- Docker & Docker Compose
- CMake
- C++ compiler (g++ or clang)
- PostgreSQL client (`psql`)

### Steps to Run the Project

1. **Clone the Repository**
   ```sh
   git clone https://github.com/MarcAdriel/Monitoring-App.git
   cd Monitoring-App

## Build and Run the Application

To build and run the C++ CRUD service and PostgreSQL database using Docker, follow these steps:

### 1. Build and Start the Containers
Run the following command to build and start the services:
```sh
docker compose up -d
```
### 2. Verify Running Containers
To check if the containers are running, use:
```sh
docker ps
```
### 2.1. Expected output:
```
CONTAINER ID   IMAGE               COMMAND                  CREATED         STATUS         PORTS                    NAMES
xxxxxxxxxxxx   crud-crud_service   "./CRUD"                 x minutes ago   Up x minutes   0.0.0.0:8080->8080/tcp   crud-crud_service-1
xxxxxxxxxxxx   postgres            "docker-entrypoint.s…"   x minutes ago   Up x minutes   0.0.0.0:5432->5432/tcp   crud_database
```

### 3. Verify Database Connection
Access PostgreSQL Container
```sh
docker exec -it crud_database psql -U postgres -d crud_db
```

Check if Tables Exist
```sh
\dt
```
### 3.1. Expected output:
```
         List of relations
 Schema | Name  | Type  |  Owner   
--------+-------+-------+----------
 public | users | table | postgres
(1 row)
```

### 4. API Endpoints:
```
Method	Endpoint	Description
GET	/users	        Fetch all users
POST	/users	        Create a new user
```
### Stop and Remove Containers:
``` sh
docker compose down -v
```







