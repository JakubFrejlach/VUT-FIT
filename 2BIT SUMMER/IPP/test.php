<?php
// Global variables for test statistics
$GLOBALS['TEST_ORDER'] = 0;
$GLOBALS['TEST_FAILED'] = 0;
$GLOBALS['TEST_SUCCESS'] = 0;

// Class for argument parsing
class args_data
{
  // Argument flags
  public $INT_ONLY = false;
  public $PARSE_ONLY = false;
  public $RECURSIVE = false;
  public $PARSE_SCRIPT = false;
  public $INT_SCRIPT = false;
  public $DIRECTORY = false;
  public $TEST_LIST = false;
  public $MATCH = false;

  // Paths for testing scripts and directories with tests
  public $REGEXP = "/^(.+)/";
  public $TEST_LIST_FILE;
  public $DIRECTORY_PATH;
  public $PARSE_SCRIPT_FILE = "parse.php";
  public $INT_SCRIPT_FILE = "interpret.py";
  public $JEXAMXML = "/pub/courses/ipp/jexamxml/jexamxml.jar";
  public $JEXAMXML_OPTIONS = "/pub/courses/ipp/jexamxml/options";

  /**
    * Parses all script arguments and sets flags in args_data class
    *
    * @param argv      script arguments
    * @param argc      script arguments count
    */
  public function parse_arguments($argv, $argc)
  {
    foreach($argv as $key => $argument)
    {
      // Ommits first argument (script name)
      if($key < 1)
      {
        continue;
      }

      if($argument == '--help' && $argc == 2)
      {
        print_help();
      }
      elseif($argument == '--int-only' && !$this->INT_ONLY)
      {
        $this->INT_ONLY = true;
      }
      elseif($argument == '--parse-only' && !$this->PARSE_ONLY)
      {
        $this->PARSE_ONLY = true;
      }
      elseif($argument == '--recursive' && !$this->RECURSIVE)
      {
        $this->RECURSIVE = true;
      }
      // Optional directory with tests
      elseif(preg_match("/^--directory=.+$/", $argument) && !$this->DIRECTORY)
      {
        $this->DIRECTORY = true;
        $this->DIRECTORY_PATH = preg_replace("/--directory=/", "", $argument, 1);
        if(!is_dir($this->DIRECTORY_PATH))
        {
          exit_msg("Directory \"$this->DIRECTORY_PATH\" doesnt exists.", 11);
        }
      }
      // Optional path to parse.php script
      elseif(preg_match("/^--parse-script=.+$/", $argument) && !$this->PARSE_SCRIPT)
      {
        $this->PARSE_SCRIPT = true;
        $this->PARSE_SCRIPT_FILE = preg_replace("/--parse-script=/", "", $argument, 1);
      }
      // Optional path to interpret.py script
      elseif(preg_match("/^--int-script=.+$/", $argument) && !$this->INT_SCRIPT)
      {
        $this->INT_SCRIPT = true;
        $this->INT_SCRIPT_FILE = preg_replace("/--int-script=/", "", $argument, 1);
      }
      // Optional path to interpret.py script
      elseif(preg_match("/^--testlist=.+$/", $argument) && !$this->TEST_LIST)
      {
        $this->TEST_LIST = true;
        $this->TEST_LIST_FILE = preg_replace("/--testlist=/", "", $argument, 1);
        if(!is_file($this->TEST_LIST_FILE))
        {
          exit_msg("File \"$this->TEST_LIST_FILE\" doesn't exists.", 11);
        }
      }
      // Optional REGEX for test names
      elseif(preg_match("/^--match=.+$/", $argument) && !$this->MATCH)
      {
        $this->MATCH = true;
        $this->REGEXP = preg_replace("/--match=/", "", $argument, 1);
      }
      else
      {
        exit_msg("Invalid argument combination.", 10);
      }
    }

    // Checks if there is no forbidden argument combinations
    if($this->INT_ONLY && ($this->PARSE_ONLY || $this->PARSE_SCRIPT))
    {
      exit_msg("Invalid argument combination.", 10);
    }
    elseif($this->PARSE_ONLY && ($this->INT_ONLY || $this->INT_SCRIPT))
    {
      exit_msg("Invalid argument combination.", 10);
    }
    elseif($this->DIRECTORY && $this->TEST_LIST)
    {
      exit_msg("Invalid argument combination.", 10);
    }

    if(!is_file($this->PARSE_SCRIPT_FILE) && !$this->INT_ONLY)
    {
      exit_msg("File \"$this->PARSE_SCRIPT_FILE\" doesn't exists.", 11);
    }
    if(!is_file($this->INT_SCRIPT_FILE) && !$this->PARSE_ONLY)
    {
      exit_msg("File \"$this->INT_SCRIPT_FILE\" doesn't exists.", 11);
    }

    if(!$this->DIRECTORY)
    {
      $this->DIRECTORY_PATH = getcwd();
    }
  }
}

/**
  * Writes error message on STDERR and termiantes script
  *
  * @param error_msg      error message to be written on STDERR
  * @param error_code     script exit code
  */
function exit_msg($error_msg, $error_code)
{
  fwrite(STDERR, "ERROR: ".$error_msg."\n");
  exit($error_code);
}

/**
 * Prints help if --help argument is given
 */
function print_help()
{
  echo "******************************************** HELP ********************************************\n";
  echo "* Script executes parse.php and interpret.py with .src test as input and generates HTML stats\n*\n";
  echo "* Script is executed:\n";
  echo "* $ php7.3 test.php [arguments]\n*\n";
  echo "* Script can be executed with optional arguments:\n";
  echo "* --help\t\tPrints help (obviously). Cannot be combined with other arguments.\n";
  echo "* --directory=<path>\tSearches for tests in given directory. Cannot be combined with --testlist=<file>\n";
  echo "* --recursive\t\tSearches for tests recursively in in other subdirectories.\n";
  echo "* --parse-script<file>\tSpecifies parse.php script. Cannot be combined with --int-only and \n*\t\t\t--int-script=<file>\n";
  echo "* --int-script<file>\tSpecifies interpret.py script. Cannot be combined with --parse-only and \n*\t\t\t--parse-script=<file>\n";
  echo "* --parse-only\t\tPerforms only parse.php tests. Cannot be combined with --int-only and \n*\t\t\t--int-script=<file>\n";
  echo "* --int-only\t\tPerforms only interpret.py tests. Cannot be combined with --parse-only and \n*\t\t\t--parse-script=<file>\n";
  echo "* --testlist=<file>\tTakes tests from given list. Cannot be combined with --directory=<path>\n";
  echo "* --match=<regexp>\tTakes only tests with name (not path), that matches given regex.\n";
  echo "**********************************************************************************************\n";
  exit(0);
}

/**
  * Searches for test files and creates missing ones then performs test
  *
  * @param name      test name
  * @param flags     class with flags from arguments
  */
function find_test($name, $flags)
{
  if(!touch("$name.in"))
  {
    exit_msg("File \"$name.in\" cannot be accessed", 11);
  }
  if(!touch("$name.out"))
  {
    exit_msg("File \"$name.out\" cannot be accessed", 11);
  }
  if(!is_file("$name.rc"))
  {
    if(!file_put_contents("$name.rc", "0"))
    {
      exit_msg("File \"$name.rc\" cannot be accessed", 11);
    }
  }
  perform_test("$name", $flags);
}

/**
  * Performs test and generates HTML log on STDOUT
  *
  * @param path      path to test
  * @param flags     class with flags from arguments
  */
function test($path, $flags)
{
  // Only when file.src is in testlist (extenstion FILES)
  if(is_file($path))
  {
    $file = preg_replace('|.*/|', '', $path);
    if(($name = preg_replace('/\.src$/', '', $file)) != $file)
    {

      if(preg_replace("$flags->REGEXP", '', $name) == NULL)
      {
        $name = preg_replace('/.src$/', '', realpath($path));
        find_test("$name", $flags);
        return;
      }
    }
    return;
  }
  elseif(!is_dir($path))
  {
    exit_msg("File or directory doesnt exists.", 11);
  }

  $dir_files = array_diff(scandir($path), array(".",".."));
  $dirs = array();

  foreach($dir_files as $object)
  {
    if($flags->RECURSIVE && is_dir("$path/$object"))
    {
        $dirs[] = "$path/$object";
        continue;
    }
    if(($name = preg_replace('/\.src$/', '', $object)) != $object)
    {
      if(preg_replace("$flags->REGEXP", "", $name) == NULL)
      {
        $name = preg_replace('/.src$/', '', realpath("$path/$name.src"));
        find_test("$name", $flags);
      }
    }
  }
  foreach ($dirs as $recursive_dir)
  {
    test($recursive_dir, $flags);
  }
}

/**
  * Performs test and generates HTML log on STDOUT
  *
  * @param path      path to test
  * @param flags     class with flags from arguments
  */
function perform_test($name, $flags)
{
  $GLOBALS['TEST_ORDER']++;
  $int_source = "$name.xml";
  $int_input = "$name.in";
  $test_ret_val = file_get_contents("$name.rc");
  if($test_ret_val === false)
  {
    exit_msg("File \"$name\" cannot be accessded.", 11);
  }

  // parse.php testing
  if(!$flags->INT_ONLY)
  {
    // Creating temporary .xml file
    if(!touch("$name.xml"))
    {
      exit_msg("Temporary file cannot failed to open.", 12);
    }

    exec("php7.3 $flags->PARSE_SCRIPT_FILE <\"$name.src\" >\"$name.xml\" 2>/dev/null", $output, $ret_val);
  }
  // interpret.py testing
  if(!$flags->PARSE_ONLY)
  {
    if($flags->INT_ONLY)
    {
      $int_source = "$name.src";
    }

    // Creating temporary .tmp file
    if(!touch("$name.tmp"))
    {
      exit_msg("Temporary file cannot failed to open.", 12);
    }

    exec("python3.6 $flags->INT_SCRIPT_FILE --source=\"$int_source\" --input=\"$int_input\" >$name.tmp 2>/dev/null", $output, $ret_val);
  }
  // Wrong return code
  if($test_ret_val != $ret_val)
  {
    generate_html_failed("$name.src", "Return value should be: $test_ret_val But it is: $ret_val");
  }
  else
  {
    // Return code ok (not 0) -> test should fail
    if($ret_val)
    {
      generate_html_success("$name.src");
    }
    // Return code ok (0) -> test should pass
    else
    {
      // XML testing
      if($flags->PARSE_ONLY)
      {
        exec("java -jar $flags->JEXAMXML \"$name.xml\" \"$name.out\" delta.xml $flags->JEXAMXML_OPTIONS", $output, $ret_val);
      }
      // interpret output testing
      else
      {
        exec("diff \"$name.tmp\" \"$name.out\"", $output, $ret_val);
      }

      // Return code ok (0), XML/interpret output ok
      if(!$ret_val)
      {
        generate_html_success("$name.src");
      }
      // Return code ok (0), XML/interpret output not ok
      else
      {
        if($flags->PARSE_ONLY)
        {
          generate_html_failed("$name.src", "Wrong XML");
        }
        else
        {
          generate_html_failed("$name.src", "Wrong interpret output");
        }
      }
    }
  }

  // Delete temporary files
  if(!$flags->INT_ONLY)
  {
    unlink("$name.xml");
  }
  if(!$flags->PARSE_ONLY)
  {
    unlink("$name.tmp");
  }
}

/**
  * Generate HTML on successful test
  *
  * @param name   name of test
  */
function generate_html_success($name)
{
 $GLOBALS['TEST_SUCCESS']++;
 echo "<tr><td>$name</td>";
 echo "<td style = \"background-color:lime\">SUCCESS</td\n>";
 echo "<td>-</td></tr>\n";
}

/**
  * Generate HTML on failed test
  *
  * @param name           name of test
  * @param description    error description
  */
function generate_html_failed($name, $description)
{
  $GLOBALS['TEST_FAILED']++;
  echo "<tr><td>$name</td>";
  echo "<td style = \"background-color:red\">FAILED</td\n>";
  echo "<td>$description</td></tr>\n";
}

/**
  * Generate HTML header and CSS styles
  *
  * @param flags      flags from script arguments
  */
function initial_html($flags)
{
  echo "<!DOCTYPE html>\n";
  echo "<html>\n";
  echo "<style>\n";
  echo "table
  {
    font-family: arial, sans-serif;
    border-collapse: collapse;
    width: 80%;
  }\n";

  echo "td, th
  {
    border: 1.5px solid black;
    text-align: center;
    padding: 8px;
  }\n";

  echo " tr:nth-child(even)
  {
    background-color: #dddddd;
  }";
  echo "h3 {text-align:center;}";
  echo "</style>\n";
  echo "<body>\n";


  $test_type = "both";
  if($flags->PARSE_ONLY)
  {
    $test_type = "parse-only";
  }
  elseif($flags->INT_ONLY)
  {
    $test_type = "int-only";
  }

  echo "<h1 align=center>Test type: $test_type</h1>\n";

  // Generate initial table row
  echo"<table align = center>
    <tr style=\"background-color:#A29C9B\">
      <th>Test</th>
      <th>Result</th>
      <th>Description</th>
    </tr>\n";
}

/**
  * Generate HTML tail with stats and time elapsed
  *
  * @param time     elapsed time
  */
function finish_html($time)
{
  echo "</table>\n";
  echo "<h3>TOTAL: ".$GLOBALS['TEST_ORDER']."</h3>";

  if($GLOBALS['TEST_ORDER'] == $GLOBALS['TEST_SUCCESS'])
  {
    echo "<h3 style=\"color:green\">ALL TESTS PASSED</h3>";
  }
  else
  {
    echo "<h3 style=\"color:red\">SOME TESTS FAILED</h3>";
    echo "<h3 style=\"color:green\">SUCCESS: ".$GLOBALS['TEST_SUCCESS']."</h3>";
    echo "<h3 style=\"color:red\">FAILED: ".$GLOBALS['TEST_FAILED']."</h3>";
  }

  $time += microtime(true);
  echo "<h3>ELAPSED TIME: ".round($time,3)." s</h3>";
  echo "</body>\n";
}

/***************************** MAIN PROGRAM *****************************/

$time = -microtime(true);
$flags = new args_data();
$flags->parse_arguments($argv, $argc);

initial_html($flags);

// Searching tests in testlist
if($flags->TEST_LIST)
{
  $fp = fopen($flags->TEST_LIST_FILE, "r");
  if(!$fp)
  {
    exit_msg("File cannot be accessed", 11);
  }
  while($line = fgets($fp))
  {
    test(trim($line), $flags);
  }
  fclose($fp);
}
// Searching tests in given directory
else
{
  test($flags->DIRECTORY_PATH, $flags);
}

finish_html($time);
?>
