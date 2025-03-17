-- Ensure we're using the correct database
\c crud_db;

-- Create `users` table if it doesn't exist
CREATE TABLE IF NOT EXISTS users (
    id SERIAL PRIMARY KEY,
    firstname VARCHAR(100) NOT NULL,
    lastname VARCHAR(100),
    email VARCHAR(100) NOT NULL,
    password VARCHAR(255) NOT NULL,
    role VARCHAR(100) NOT NULL
    );

-- Optional: Insert sample data
INSERT INTO users (firstname, lastname, email, password, role) VALUES ('Alice', 'Toh', 'alice@gmail.com', 'password', 'user');
INSERT INTO users (firstname, lastname, email, password, role) VALUES ('Lawrence', 'Chan', 'chan@gmail.com', 'password', 'admin');
