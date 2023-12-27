-- 001_init.sql

CREATE TABLE IF NOT EXISTS qe_tag
(
    id        SERIAL PRIMARY KEY,
    name      TEXT    NOT NULL,
    hex_color INTEGER NOT NULL
);

CREATE TABLE IF NOT EXISTS qe_question
(
    id                 SERIAL PRIMARY KEY,
    parent             INTEGER   NOT NULL DEFAULT -1,
    title              TEXT      NOT NULL,
    type               INTEGER   NOT NULL DEFAULT -1,
    estimated_time_sec INTEGER   NOT NULL DEFAULT 10,
    score              INTEGER   NOT NULL DEFAULT 1,
    is_published       BOOLEAN   NOT NULL DEFAULT FALSE,
    reference_count    INTEGER   NOT NULL DEFAULT 0,
    correct_count      INTEGER   NOT NULL DEFAULT 0,
    created_at         TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    updated_at         TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE IF NOT EXISTS qe_question_content
(
    id            SERIAL PRIMARY KEY,
    content_type  INTEGER NOT NULL,
    content       TEXT    NOT NULL,
    content_index INTEGER NOT NULL,
    question_id   INTEGER NOT NULL,
    FOREIGN KEY (question_id) REFERENCES qe_question (id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS qe_question_sub_questions
(
    id                 SERIAL PRIMARY KEY,
    sub_question_id    INTEGER NOT NULL,
    question_id        INTEGER NOT NULL,
    sub_question_index INTEGER NOT NULL,
    FOREIGN KEY (sub_question_id) REFERENCES qe_question (id) ON DELETE CASCADE,
    FOREIGN KEY (question_id) REFERENCES qe_question (id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS qe_question_tag
(
    id          SERIAL PRIMARY KEY,
    tag_id      INTEGER NOT NULL,
    question_id INTEGER NOT NULL,
    priority    INTEGER NOT NULL,
    FOREIGN KEY (tag_id) REFERENCES qe_tag (id) ON DELETE CASCADE,
    FOREIGN KEY (question_id) REFERENCES qe_question (id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS qe_answer
(
    id          SERIAL PRIMARY KEY,
    question_id INTEGER NOT NULL,
    is_correct  BOOLEAN NOT NULL DEFAULT FALSE,
    FOREIGN KEY (question_id) REFERENCES qe_question (id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS qe_answer_content
(
    id            SERIAL PRIMARY KEY,
    content_type  INTEGER NOT NULL,
    content       TEXT    NOT NULL,
    content_index INTEGER NOT NULL,
    answer_id     INTEGER NOT NULL,
    FOREIGN KEY (answer_id) REFERENCES qe_answer (id) ON DELETE CASCADE
);