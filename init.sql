-- Ensure we're using the correct database
\c crud_db;

-- Create `users` table if it doesn't exist
CREATE TABLE IF NOT EXISTS users (
    id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    age INT NOT NULL
    );

-- Optional: Insert sample data
INSERT INTO users (name, age) VALUES ('Alice', 25), ('Bob', 30);
