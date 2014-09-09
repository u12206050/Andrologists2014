CREATE TABLE images
(
	id bigserial NOT NULL,
	filename character varying(200) NOT NULL,
	"timestamp" bigint NOT NULL,
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
	userName varchar(50) NOT NULL,
	password varchar(30) NOT NULL,
	active boolean NOT NULL,
	CONSTRAINT users_primary_key PRIMARY KEY (userName)
);

CREATE TYPE Gender AS 
ENUM ("M", "F");

CREATE TABLE cases
(
	id bigserial NOT NULL,
	description text,
	subName text,
	subSurname text,
	subGender Gender,
	subAge smallint,
	image_id bigint NOT NULL,
	status int,
	progress smallint,
	userName varchar(50) NOT NULL,
	numResults smallint,
	CONSTRAINT cases_primary_key PRIMARY KEY (id),
	CONSTRAINT case_image_relationship FOREIGN KEY (image_id)
		REFERENCES images (id) MATCH SIMPLE
		ON UPDATE NO ACTION ON DELETE NO ACTION,
	CONSTRAINT case_user_relationship FOREIGN KEY (userName)
		REFERENCES users (userName) MATCH SIMPLE
		ON UPDATE NO ACTION ON DELETE NO ACTION
);

CREATE TABLE caseResults
(
	id bigserial NOT NULL,
	image_id bigint NOT NULL,
	case_id bigint NOT NULL,
	percentageMatch smallint NOT NULL,
	randomIdentifier varchar(20),
	CONSTRAINT case_results_primary_key PRIMARY KEY (id),
	CONSTRAINT caseResult_image_relationship FOREIGN KEY (image_id)
		REFERENCES images (id) MATCH SIMPLE
		ON UPDATE NO ACTION ON DELETE NO ACTION,
	CONSTRAINT caseResult_case_relationship FOREIGN KEY (case_id)
		REFERENCES cases (id) MATCH SIMPLE
		ON UPDATE NO ACTION ON DELETE NO ACTION
);
