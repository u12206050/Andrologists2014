CREATE EXTENSION pgcrypto;

INSERT INTO users(
            username, password, active)
    VALUES ('admin', crypt('5656674d2a4c675f8bf727885ff75ea607256c398111a524980ea91ef864f8bd', '2a068uKrXaZiFsbdet62kkZSSOida'), true);


SELECT * FROM users;
/*Default password 'qfrss' = 5656674d2a4c675f8bf727885ff75ea607256c398111a524980ea91ef864f8bd */
SELECT crypt('5656674d2a4c675f8bf727885ff75ea607256c398111a524980ea91ef864f8bd', '2a068uKrXaZiFsbdet62kkZSSOida') AS code;