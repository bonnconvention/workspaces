<?php
    /* all live-data in:
    sites/all/modules/a_wusel_migration/data_sources/
    */
    /* based on: drupal.org/node/1269066#comment-4988994 */
    /* and:      drupal.org/node/1190958#comment-4616032 */
abstract class Wusel_Basic_Migration extends Migration {
  public function __construct() {
    // Always call the parent constructor first for basic setup
    parent::__construct(MigrateGroup::getInstance('WuselMigrate'));
  }
}

class Wusel_Step1_UserMigration extends Wusel_Basic_Migration {
  public function __construct() {
    parent::__construct();
    $this->description = t('Import an CSV-file (only "Account"-fields)');
    $columns = array();
    $this->source = new MigrateSourceCSV(DRUPAL_ROOT . '/' . drupal_get_path('module', 'user_import') . '/data_sources/original_userlist.csv', $columns, array('header_rows' => 1));
    $this->destination = new MigrateDestinationUser();
    $this->map = new MigrateSQLMap($this->machineName,
        array('uid' => array( // this field is used to connect user und profile2
                'type' => 'int',
                'length' => 10,
                'not null' => TRUE,
                'description' => t('') // description never used
              )
             ),
        MigrateDestinationUser::getKeySchema()
    );
/*
    // Mapped fields
    $this->addSimpleMappings(array('name'));
    $this->addFieldMapping('is_new')
	 ->defaultValue(TRUE);
    $this->addFieldMapping('uid', 'uid');
    $this->addFieldMapping('mail', 'mail');
*/
// Mapped fields
    $this->addSimpleMappings(array('name'));
    $this->addFieldMapping('uid', 'uid');
    $this->addFieldMapping('mail', 'mail')
      ->defaultValue('')
      ->description(t('Email address'));
    $this->addFieldMapping('init')
      ->defaultValue('')
      ->description(t('Email address used for initial account creation'));
    $this->addFieldMapping('pass', 'password')
      ->defaultValue('asdf')
      ->description(t("User's password (plain text)"));
    $this->addFieldMapping('is_new')
      ->defaultValue(TRUE)
      ->description(t('Build the new user (0|1)'));
    $this->addFieldMapping('roles')
      ->defaultValue(DRUPAL_AUTHENTICATED_RID)
      ->description(DRUPAL_AUTHENTICATED_RID . t(' = "authenticated user"'));
    $this->addFieldMapping('theme')
      ->defaultValue('')
      ->description(t("User's default theme"));
    $this->addFieldMapping('signature')
      ->defaultValue('')
      ->description(t("User's signature"));
    $this->addFieldMapping('signature_format')
      ->defaultValue('filtered_html')
      ->description(t('Which filter applies to this signature'));
    $this->addFieldMapping('created')
      ->defaultValue(time())
      ->description(t('UNIX timestamp of user creation date'));
    $this->addFieldMapping('access')
      ->defaultValue(0)
      ->description(t('UNIX timestamp for previous time user accessed the site'));
    $this->addFieldMapping('login')
      ->defaultValue(0)
      ->description(t('UNIX timestamp for user\'s last login'));
    $this->addFieldMapping('status')
      ->defaultValue(1)
      ->description(t('Whether the user is active(1) or blocked(0)'));
    $this->addFieldMapping('timezone')
      ->defaultValue(t('Europe/Berlin')) // 'America/Los_Angeles', 'Europe/Berlin', 'UTC', ... from drupal.org/node/714214
      ->description(t("User's time zone"));
    $this->addFieldMapping('language')
      ->defaultValue(t('en')) // e.g.: 'en', 'fr', 'de', ...
      ->description(t("User's default language"));
    $this->addFieldMapping('picture')
      ->defaultValue(0) 
      ->description(t('Avatar of the user'));
  }
}

class Wusel_Step2_PersonalInfoMigration extends Wusel_Basic_Migration {
  public function __construct() {
    parent::__construct();
    global $user;
    $this->description = t('Import an CSV-file with Profile2-fields ("memberlist"-fields)');
    $columns = array();
    // TIP: delete ", array('header_rows' => 1)" in the next line, if the CSV-file has NO header-line
    $this->source = new MigrateSourceCSV(DRUPAL_ROOT . '/' . drupal_get_path('module', 'user_import') . '/data_sources/original_userlist.csv', $columns, array('header_rows' => 1));
    // Declare migration 'Wusel_Step1_User' a dependency in migration 'Wusel_Step2_Memberlist' to have them run in the right order, if needed:
    $this->dependencies = array('Wusel_Step1_User');
    $this->destination = new MigrateDestinationProfile2('personal_information');  // 'memberlist' is the "Machine name" of the profile2-"Profile type"
    $this->map = new MigrateSQLMap($this->machineName,
        array('uid' => array( // this field is used to connect user und profile2
                'type' => 'int',
                'length' => 10,
                'not null' => TRUE,
                'description' => t('') // description never used
              )
             ),
        MigrateDestinationProfile2::getKeySchema()
    );

    // Connecting the profile2 to the user:    
    $this->addFieldMapping('uid', 'uid')
         ->sourceMigration('Wusel_Step1_User')  // If your user migration class was named 'MyUserMigration', the string is 'MyUser'
         ->description(t('The assignment of profile2-items to the respective user'));

    $this->addFieldMapping('field_first_name', 'first_name');
    $this->addFieldMapping('field_last_name', 'last_name');
    $this->addFieldMapping('field_country_of_origin', 'country_origin');
    $this->addFieldMapping('field_email', 'email');
    $this->addFieldMapping('field_additional_information_bio', 'biography');
    $this->addFieldMapping('field_title', 'title');
    // Unmapped fields (this fields are in core and not needed as profile2-fields)
    $this->addUnmigratedSources(array('mail', 'password'));
  }

  public function fixTimestamp($date) {
    // enable empty (= unknown) birthday-string:
    if (strlen($date) > 0) {
      $date = substr($date,0,10) . 'T12:00:00'; // we add 'twelve o'clock in the daytime' for automatic compensation of a website time zone difference to UTC
    }
    return $date;
  } 
}

class Wusel_Step3_ContactInfoMigration extends Wusel_Basic_Migration {
  public function __construct() {
    parent::__construct();
    global $user;
    $this->description = t('Import an CSV-file with Profile2-fields ("memberlist"-fields)');
    $columns = array();
    // TIP: delete ", array('header_rows' => 1)" in the next line, if the CSV-file has NO header-line
    $this->source = new MigrateSourceCSV(DRUPAL_ROOT . '/' . drupal_get_path('module', 'user_import') . '/data_sources/original_userlist.csv', $columns, array('header_rows' => 1));
    // Declare migration 'Wusel_Step1_User' a dependency in migration 'Wusel_Step2_Memberlist' to have them run in the right order, if needed:
    $this->dependencies = array('Wusel_Step1_User');
    $this->destination = new MigrateDestinationProfile2('official_contact_information');  // 'memberlist' is the "Machine name" of the profile2-"Profile type"
    $this->map = new MigrateSQLMap($this->machineName,
        array('uid' => array( // this field is used to connect user und profile2
                'type' => 'int',
                'length' => 10,
                'not null' => TRUE,
                'description' => t('') // description never used
              )
             ),
        MigrateDestinationProfile2::getKeySchema()
    );

    // Connecting the profile2 to the user:    
    $this->addFieldMapping('uid', 'uid')
         ->sourceMigration('Wusel_Step1_User')  // If your user migration class was named 'MyUserMigration', the string is 'MyUser'
         ->description(t('The assignment of Official contact information profile2-items to the respective user'));

    $this->addFieldMapping('field_name_of_institution', 'institution_name');
    $this->addFieldMapping('field_full_address_of_institutio', 'institution_address');
    $this->addFieldMapping('field_telephone', 'phone');
    $this->addFieldMapping('field_official_email', 'official_email');
    // Unmapped fields (this fields are in core and not needed as profile2-fields)
    $this->addUnmigratedSources(array('mail', 'password'));
  }
 
 /* Define the prepareRow function to unset any empty fields before migration. */
 /* 
   public function prepareRow($row) {
    foreach($row as $field=>$value){
      if (empty($value) || $value == ""){
        //unset($row->$field);
	$row->$field = "__UNSET__";
      }
    }
    return TRUE;
  }*/
}

class Wusel_Step3_TCFunctionMigration extends Wusel_Basic_Migration {
  public function __construct() {
    parent::__construct();
    global $user;
    $this->description = t('Import an CSV-file with Profile2-fields ("memberlist"-fields)');
    $columns = array();
    $this->source = new MigrateSourceCSV(DRUPAL_ROOT . '/' . drupal_get_path('module', 'user_import') . '/data_sources/original_userlist.csv', $columns, array('header_rows' => 1));
    
    // Declare migration 'Wusel_Step1_User' a dependency in migration 'Wusel_Step2_Memberlist' to have them run in the right order, if needed:
    $this->dependencies = array('Wusel_Step1_User');
    $this->destination = new MigrateDestinationProfile2('tc_function');  
    $this->map = new MigrateSQLMap($this->machineName,
        array('uid' => array( // this field is used to connect user und profile2
                'type' => 'int',
                'length' => 10,
                'not null' => TRUE,
                'description' => t('') // description never used
              )
             ),
        MigrateDestinationProfile2::getKeySchema()
    );

    // Connecting the profile2 to the user:    
    $this->addFieldMapping('uid', 'uid')
         ->sourceMigration('Wusel_Step1_User')  // If your user migration class was named 'MyUserMigration', the string is 'MyUser'
         ->description(t('The assignment of Official contact information profile2-items to the respective user'));

    $this->addFieldMapping('field_profile_role', 'tc_role');
    $this->addFieldMapping('field_regional_representative_tc', 'regional_rep');
    $this->addFieldMapping('field_expert', 'expert');
    $this->addFieldMapping('field_ngo_representative', 'ngo_rep');
    $this->addFieldMapping('field_ngo_representative:format')
         ->defaultValue('plain_text');    
    $this->addFieldMapping('field_ngo_representative:language')
         ->defaultValue('und');    
    $this->addFieldMapping('field_observer', 'observer')
         ->defaultValue('');    
    $this->addFieldMapping('field_observer:format')
         ->defaultValue('plain_text');    
    $this->addFieldMapping('field_observer:language')
         ->defaultValue('und');    
    $this->addFieldMapping('field_guest', 'guest')
         ->defaultValue('');    
    $this->addFieldMapping('field_guest:format')
         ->defaultValue('plain_text');    
    $this->addFieldMapping('field_guest:language')
         ->defaultValue('und');    
    $this->addFieldMapping('field_tc_functions', 'tc_function')
         ->defaultValue('');    
    $this->addFieldMapping('field_tc_functions:format')
         ->defaultValue('plain_text');    
    $this->addFieldMapping('field_tc_functions:language')
         ->defaultValue('und');   
    $this->addFieldMapping('languge')
      ->defaultValue(t('en')); 
    // Unmapped fields (this fields are in core and not needed as profile2-fields)
    $this->addUnmigratedSources(array('mail', 'password'));
  }
}
?>
