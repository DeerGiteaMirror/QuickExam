-- 002_question_create_time.sql

CREATE TABLE IF NOT EXISTS qe_question_operate_time
(
    id         SERIAL PRIMARY KEY,
    belong_id  INTEGER   NOT NULL,
    created_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (belong_id) REFERENCES qe_question (id)
);
