<?php
$curdir_slib = dirname(__FILE__);

class SLib {
	static $CONN = null;
	static $CONFIG = null;
	
	static function db_connection() {
		if (SLib::$CONN != null)
			return SLib::$CONN;
		
		SLib::$CONN = new PDO(
			'mysql:host='.SLib::$CONFIG['db']['host'].';dbname='.SLib::$CONFIG['db']['dbname'].';charset=utf8',
			SLib::$CONFIG['db']['username'],
			SLib::$CONFIG['db']['userpass']
		);
		return SLib::$CONN;
	}
}

// load config
include_once ($curdir_slib."/conf.d/config.php");
SLib::$CONFIG = $config;
