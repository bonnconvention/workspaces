<?php

$databases['default']['default'] = array(
 'driver' => 'mysql',
 'database' => 'database',
 'username' => 'user',
 'password' => 'password',
 'host' => 'localhost',
 'prefix' => '',
);
$drupal_hash_salt = 'TEST';

$conf['css_gzip_compression'] = FALSE;
$conf['js_gzip_compression'] = FALSE;
$conf['theme_debug'] = TRUE;
$conf['file_temporary_path'] = '/tmp';
$conf['file_private_path'] = '/path/to/files/private';

$update_free_access = FALSE;

$cookie_domain = '.cms.local';

$base_url = 'https://tcworkspace.aewa.info';

$conf['smtp_from'] = 'email@emai..com';
$conf['smtp_host'] = 'smtp.host.com';
$conf['smtp_hostbackup'] = '';
$conf['smtp_on'] = '1';
$conf['smtp_password'] = 'smtp-password';
$conf['smtp_port'] = '465';
$conf['smtp_previous_mail_system'] = 'DefaultMailSystem';
$conf['smtp_protocol'] = 'ssl';
$conf['smtp_queue'] = 0;
$conf['smtp_queue_fail'] = 1;
$conf['smtp_reroute_address'] = '';
$conf['smtp_username'] = 'smtp-username';

$conf['edw_healthcheck_user'] = '';
$conf['edw_healthcheck_pass'] = '';