<?php
	session_start();
	$curdir = dirname(__FILE__);
	include_once ($curdir."/slib.php");
	
	if(!isset($_SESSION['userid']) && !isset($_SESSION['role'])){
		header("Location: index.php");
		exit;
	}
	
	unset($_SESSION['userid']);
	unset($_SESSION['role']);
	header("Location: index.php");
