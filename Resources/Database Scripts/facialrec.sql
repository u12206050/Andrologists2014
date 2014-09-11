--
-- PostgreSQL database dump
--

-- Dumped from database version 9.2.2
-- Dumped by pg_dump version 9.2.2
-- Started on 2014-09-09 14:50:10

SET statement_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;

--
-- TOC entry 179 (class 3079 OID 11727)
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- TOC entry 1992 (class 0 OID 0)
-- Dependencies: 179
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

--
-- TOC entry 533 (class 1247 OID 17691)
-- Name: gender; Type: TYPE; Schema: public; Owner: postgres
--

CREATE TYPE gender AS ENUM (
    'M',
    'F'
);


ALTER TYPE public.gender OWNER TO postgres;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- TOC entry 178 (class 1259 OID 17743)
-- Name: cameras; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE cameras (
    id bigint NOT NULL,
    ipaddress character varying(20),
    location character varying(200) NOT NULL
);


ALTER TABLE public.cameras OWNER TO postgres;

--
-- TOC entry 177 (class 1259 OID 17741)
-- Name: cameras_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE cameras_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.cameras_id_seq OWNER TO postgres;

--
-- TOC entry 1993 (class 0 OID 0)
-- Dependencies: 177
-- Name: cameras_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE cameras_id_seq OWNED BY cameras.id;


--
-- TOC entry 176 (class 1259 OID 17718)
-- Name: caseresults; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE caseresults (
    id bigint NOT NULL,
    image_id bigint NOT NULL,
    case_id bigint NOT NULL,
    percentagematch smallint NOT NULL,
    randomidentifier character varying(20)
);


ALTER TABLE public.caseresults OWNER TO postgres;

--
-- TOC entry 175 (class 1259 OID 17716)
-- Name: caseresults_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE caseresults_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.caseresults_id_seq OWNER TO postgres;

--
-- TOC entry 1994 (class 0 OID 0)
-- Dependencies: 175
-- Name: caseresults_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE caseresults_id_seq OWNED BY caseresults.id;


--
-- TOC entry 174 (class 1259 OID 17697)
-- Name: cases; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE cases (
    id bigint NOT NULL,
    description text,
    subname text,
    subsurname text,
    subgender gender,
    subage smallint,
    image_id bigint NOT NULL,
    status integer,
    progress smallint,
    username character varying(50) NOT NULL,
    numresults smallint
);


ALTER TABLE public.cases OWNER TO postgres;

--
-- TOC entry 173 (class 1259 OID 17695)
-- Name: cases_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE cases_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.cases_id_seq OWNER TO postgres;

--
-- TOC entry 1995 (class 0 OID 0)
-- Dependencies: 173
-- Name: cases_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE cases_id_seq OWNED BY cases.id;


--
-- TOC entry 171 (class 1259 OID 17674)
-- Name: faces; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE faces (
    id bigint NOT NULL,
    filename character varying(200) NOT NULL,
    image_id bigint NOT NULL,
    isfemale boolean
);


ALTER TABLE public.faces OWNER TO postgres;

--
-- TOC entry 170 (class 1259 OID 17672)
-- Name: faces_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE faces_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.faces_id_seq OWNER TO postgres;

--
-- TOC entry 1996 (class 0 OID 0)
-- Dependencies: 170
-- Name: faces_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE faces_id_seq OWNED BY faces.id;


--
-- TOC entry 169 (class 1259 OID 17666)
-- Name: images; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE images (
    id bigint NOT NULL,
    filename character varying(200) NOT NULL,
    "timestamp" bigint NOT NULL,
    camera_id bigint DEFAULT 0
);


ALTER TABLE public.images OWNER TO postgres;

--
-- TOC entry 168 (class 1259 OID 17664)
-- Name: images_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE images_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.images_id_seq OWNER TO postgres;

--
-- TOC entry 1997 (class 0 OID 0)
-- Dependencies: 168
-- Name: images_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE images_id_seq OWNED BY images.id;


--
-- TOC entry 172 (class 1259 OID 17685)
-- Name: users; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE users (
    username character varying(50) NOT NULL,
    password character varying(30) NOT NULL,
    active boolean NOT NULL
);


ALTER TABLE public.users OWNER TO postgres;

--
-- TOC entry 1953 (class 2604 OID 17746)
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY cameras ALTER COLUMN id SET DEFAULT nextval('cameras_id_seq'::regclass);


--
-- TOC entry 1952 (class 2604 OID 17721)
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY caseresults ALTER COLUMN id SET DEFAULT nextval('caseresults_id_seq'::regclass);


--
-- TOC entry 1951 (class 2604 OID 17700)
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY cases ALTER COLUMN id SET DEFAULT nextval('cases_id_seq'::regclass);


--
-- TOC entry 1950 (class 2604 OID 17677)
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY faces ALTER COLUMN id SET DEFAULT nextval('faces_id_seq'::regclass);


--
-- TOC entry 1948 (class 2604 OID 17669)
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY images ALTER COLUMN id SET DEFAULT nextval('images_id_seq'::regclass);


--
-- TOC entry 1984 (class 0 OID 17743)
-- Dependencies: 178
-- Data for Name: cameras; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY cameras (id, ipaddress, location) FROM stdin;



--
-- TOC entry 1998 (class 0 OID 0)
-- Dependencies: 177
-- Name: cameras_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('cameras_id_seq', 1, false);


--
-- TOC entry 1982 (class 0 OID 17718)
-- Dependencies: 176
-- Data for Name: caseresults; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY caseresults (id, image_id, case_id, percentagematch, randomidentifier) FROM stdin;



--
-- TOC entry 1999 (class 0 OID 0)
-- Dependencies: 175
-- Name: caseresults_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('caseresults_id_seq', 1, false);


--
-- TOC entry 1980 (class 0 OID 17697)
-- Dependencies: 174
-- Data for Name: cases; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY cases (id, description, subname, subsurname, subgender, subage, image_id, status, progress, username, numresults) FROM stdin;



--
-- TOC entry 2000 (class 0 OID 0)
-- Dependencies: 173
-- Name: cases_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('cases_id_seq', 1, false);


--
-- TOC entry 1977 (class 0 OID 17674)
-- Dependencies: 171
-- Data for Name: faces; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY faces (id, filename, image_id, isfemale) FROM stdin;



--
-- TOC entry 2001 (class 0 OID 0)
-- Dependencies: 170
-- Name: faces_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('faces_id_seq', 1, false);


--
-- TOC entry 1975 (class 0 OID 17666)
-- Dependencies: 169
-- Data for Name: images; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY images (id, filename, "timestamp", camera_id) FROM stdin;



--
-- TOC entry 2002 (class 0 OID 0)
-- Dependencies: 168
-- Name: images_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('images_id_seq', 1, false);


--
-- TOC entry 1978 (class 0 OID 17685)
-- Dependencies: 172
-- Data for Name: users; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY users (username, password, active) FROM stdin;



--
-- TOC entry 1965 (class 2606 OID 17750)
-- Name: cameras_ipaddress_key; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY cameras
    ADD CONSTRAINT cameras_ipaddress_key UNIQUE (ipaddress);


--
-- TOC entry 1967 (class 2606 OID 17748)
-- Name: cameras_primary_key; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY cameras
    ADD CONSTRAINT cameras_primary_key PRIMARY KEY (id);


--
-- TOC entry 1963 (class 2606 OID 17723)
-- Name: case_results_primary_key; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY caseresults
    ADD CONSTRAINT case_results_primary_key PRIMARY KEY (id);


--
-- TOC entry 1961 (class 2606 OID 17705)
-- Name: cases_primary_key; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY cases
    ADD CONSTRAINT cases_primary_key PRIMARY KEY (id);


--
-- TOC entry 1957 (class 2606 OID 17679)
-- Name: faces_primary_key; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY faces
    ADD CONSTRAINT faces_primary_key PRIMARY KEY (id);


--
-- TOC entry 1955 (class 2606 OID 17671)
-- Name: images_primary_key; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY images
    ADD CONSTRAINT images_primary_key PRIMARY KEY (id);


--
-- TOC entry 1959 (class 2606 OID 17689)
-- Name: users_primary_key; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY users
    ADD CONSTRAINT users_primary_key PRIMARY KEY (username);


--
-- TOC entry 1968 (class 2606 OID 17751)
-- Name: camera_image_relationship; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY images
    ADD CONSTRAINT camera_image_relationship FOREIGN KEY (camera_id) REFERENCES cameras(id);


--
-- TOC entry 1970 (class 2606 OID 17706)
-- Name: case_image_relationship; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY cases
    ADD CONSTRAINT case_image_relationship FOREIGN KEY (image_id) REFERENCES images(id);


--
-- TOC entry 1971 (class 2606 OID 17711)
-- Name: case_user_relationship; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY cases
    ADD CONSTRAINT case_user_relationship FOREIGN KEY (username) REFERENCES users(username);


--
-- TOC entry 1973 (class 2606 OID 17729)
-- Name: caseresult_case_relationship; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY caseresults
    ADD CONSTRAINT caseresult_case_relationship FOREIGN KEY (case_id) REFERENCES cases(id);


--
-- TOC entry 1972 (class 2606 OID 17724)
-- Name: caseresult_image_relationship; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY caseresults
    ADD CONSTRAINT caseresult_image_relationship FOREIGN KEY (image_id) REFERENCES images(id);


--
-- TOC entry 1969 (class 2606 OID 17680)
-- Name: face_image_relationship; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY faces
    ADD CONSTRAINT face_image_relationship FOREIGN KEY (image_id) REFERENCES images(id);


--
-- TOC entry 1991 (class 0 OID 0)
-- Dependencies: 5
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


-- Completed on 2014-09-09 14:50:10

--
-- PostgreSQL database dump complete
--

