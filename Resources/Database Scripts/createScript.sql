﻿CREATE TABLE images
(
	id bigserial NOT NULL,
	filename character varying(200) NOT NULL,
	timedate bigint NOT NULL,
	location text DEFAULT 'QFRSS',
	CONSTRAINT images_primary_key PRIMARY KEY (id)
);

CREATE TABLE faces
(
	id bigserial NOT NULL,
	filename character varying(200) NOT NULL,
	image_id bigint NOT NULL,
        isFemale boolean,
	CONSTRAINT faces_primary_key PRIMARY KEY (id),
	CONSTRAINT face_image_relationship FOREIGN KEY (image_id)
		REFERENCES images (id) MATCH SIMPLE
		ON UPDATE NO ACTION ON DELETE NO ACTION
);

CREATE TABLE users
(
	username varchar(50) NOT NULL,
	password varchar(100) NOT NULL,
	active boolean NOT NULL,
	CONSTRAINT users_primary_key PRIMARY KEY (username)
);

CREATE TABLE cases
(
	id bigserial NOT NULL,
	description text,
	sub_name text,
	sub_surname text,
	sub_gender char(1),
	sub_age smallint,
	image_id bigint NOT NULL,
	status text,
	progress smallint,
	username varchar(50) NOT NULL,
	num_results smallint,
	CONSTRAINT cases_primary_key PRIMARY KEY (id),
	CONSTRAINT case_image_relationship FOREIGN KEY (image_id)
		REFERENCES images (id) MATCH SIMPLE
		ON UPDATE NO ACTION ON DELETE NO ACTION,
	CONSTRAINT case_user_relationship FOREIGN KEY (username)
		REFERENCES users (username) MATCH SIMPLE
		ON UPDATE NO ACTION ON DELETE NO ACTION
);

CREATE TABLE case_results
(
	id bigserial NOT NULL,
	face_id bigint NOT NULL,
	case_id bigint NOT NULL,
	percentage_match smallint NOT NULL,
	random_identifier varchar(20),
	CONSTRAINT case_results_primary_key PRIMARY KEY (id),
	CONSTRAINT case_result_case_relationship FOREIGN KEY (case_id)
		REFERENCES cases (id) MATCH SIMPLE
		ON UPDATE NO ACTION ON DELETE NO ACTION,
	CONSTRAINT case_result_face_relationship FOREIGN KEY (face_id)
		REFERENCES faces (id) MATCH SIMPLE
		ON UPDATE NO ACTION ON DELETE NO ACTION
);

CREATE EXTENSION pgcrypto;

INSERT INTO users(
            username, password, active)
    VALUES ('admin', crypt('5656674d2a4c675f8bf727885ff75ea607256c398111a524980ea91ef864f8bd', '2a068uKrXaZiFsbdet62kkZSSOida'), true);

