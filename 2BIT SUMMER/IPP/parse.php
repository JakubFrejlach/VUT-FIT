<?php
// Global variables for argument parsing and XML generator
$GLOBALS['instruction_order'] = 0;
$GLOBALS['help'] = false;
$GLOBALS['stat'] = false;
$GLOBALS['stats_params'] = false;
$GLOBALS['file_name'] = "";

// Class for token, holding data and type
class t_token
{
  public $type;
  public $data;
}

// Class for STATP extension
class t_stats
{
  private $comments_count = 0;
  private $jump_count = 0;
  private $label_count = 0;
  private $labels = array();

  /**
   * Process comment and increments comment stats
   *
   * @param line      line of source code
   * @return          line without a comment
   */
  public function handle_comments($line)
  {
    $line = preg_replace("/#(.*$)/", "", $line, -1, $count);
    $line = trim($line);

    $this->comments_count += $count;
    return $line;
  }
  /**
   * Counts jumps
   *
   * @param parts     token with opcode
   */
  public function handle_jump($token)
  {
    if(preg_match("/JUMP|JUMPIFEQ|JUMPIFNEQ/", $token->data))
    {
      $this->jump_count++;
    }
  }

  /**
   * Counts labels
   *
   * @param parts     token with label
   */
  public function handle_label($token)
  {
    if(!in_array($token->data, $this->labels))
    {
      $this->labels[] = $token->data;
    }
  }

  /**
   * Prints STATP stats into file
   *
   * @param argv     script arguments
   */
  public function print_stats($argv)
  {
    // Opens and checks file
    $fp = fopen($GLOBALS['file_name'], "w");
    if($fp == FALSE)
    {
      fwrite(STDERR, "ERROR:Failed to open file.\n");
      exit(11);
    }

    // Loops through script arguments and prints stats in given order
    foreach ($argv as $key => $value)
    {
      switch($value)
      {
        case "--loc":
          fwrite($fp, $GLOBALS['instruction_order']."\n");
          break;
        case "--comments":
          fwrite($fp, "$this->comments_count\n");
          break;
        case "--labels":
          fwrite($fp, count($this->labels)."\n");
          break;
        case "--jumps":
          fwrite($fp, "$this->jump_count\n");
          break;
        default:
          break;
      }
    }
    fclose($fp);
  }
}
/**
 * Prints help if --help argument is given
 */
function print_help()
{
  echo "******************************************** HELP ********************************************\n";
  echo "* Script reads instructions in IPPcode19 from STDIN, verifies them and writes them in XML to STDOUT\n*\n";
  echo "* Script is executed:\n";
  echo "* $ php7.3 parse.php [arguments]\n*\n";
  echo "* Script can be executed with optional arguments:\n";
  echo "* --help\t\tPrints help (obviously). Cannot be combined with other arguments.\n";
  echo "* --stats=<file>\tPrints additional stats into <file> when combined with arguments below.\n*\n";
  echo "* Following arguments can all be combined and can be used multiple times:\n";
  echo "* --loc\t\t\tPrints total count of instructions in source code.\n";
  echo "* --comments\t\tPrints total count of comments in source code.\n";
  echo "* --labels\t\tPrints total count of labels in source code.\n";
  echo "* --jumps\t\tPrints total count of jump instructions in source code.\n";
  echo "**********************************************************************************************\n";
  exit(0);
}

/**
 * Appends token in token array
 *
 * @param token         token that should be appended
 * @param $token_array  array of tokens for syntax analysis
 * @param $type         analyzed type of token
 * @param $data         analyzed token data
 */
function add_token($token, &$token_array, $type, $data)
{
  $token->type = $type;
  $token->data = $data;
  $token_array[] = $token;
}

/**
 * Lexically analysis line with source code
 *
 * @param line         line with source code
 * @param $stats       class with stats for STATP extension
 * @return             array of tokens
 */
function lexical_analysis($line, $stats)
{
  $line = $stats->handle_comments($line);

  // Split line into lexems
  $parts = preg_split('/\s+/', $line, -1, PREG_SPLIT_NO_EMPTY);
  $token_array = array();

  // Perform analysis for each lexeme
  foreach ($parts as $key => $lex)
  {
    $token = new t_token();

    // First lexeme must be opcode
    if($key == 0)
    {
      add_token($token, $token_array, "opcode", strtoupper($lex));
      $stats->handle_jump($token);
      continue;
    }

    // Variable case
    if(preg_match("/^(GF|LF|TF)@[a-zA-Z_\-$&%*!?][a-zA-Z0-9_\-$&%*!?]*$/", $lex))
    {
      add_token($token, $token_array, "var", $lex);
      continue;
    }
    // Bool or nil constant case
    elseif(preg_match("/^nil@nil|bool@(true|false)$/", $lex))
    {
      add_token($token, $token_array, "const", $lex);
      continue;
    }
    // Integer constant case
    elseif(preg_match("/^int@([-+]?[0-9]+)$/", $lex))
    {
      add_token($token, $token_array, "const", $lex);
      continue;
    }
    // String constant case
    elseif(preg_match("/^string@(([\x{0021}\x{0022}\x{0024}-\x{005B}\x{005D}-\x{FFFF}])|(\\\\[0-9][0-9][0-9]))*$/u", $lex))
    {
      add_token($token, $token_array, "const", $lex);
      continue;
    }
    // Type case
    elseif(preg_match("/^(int|string|bool)$/", $lex) && $token_array[0]->data == "READ")
    {
      add_token($token, $token_array, "type", $lex);
      continue;
    }
    // Label case
    elseif(preg_match("/^[a-zA-Z_\-$&%*!?][a-zA-Z0-9_\-$&%*!?]*$/", $lex) && $token_array[count($token_array)-1]->type == "opcode")
    {
      add_token($token, $token_array, "label", $lex);

      if($token_array[0]->data == "LABEL")
      {
        $stats->handle_label($token);
      }
      continue;
    }
    // Not recognized lexeme -> ERROR
    else
    {
      fwrite(STDERR, "ERROR:Other lexical or syntax error.\n");
      exit(23);
    }
  }

  return $token_array;
}

/**
 * Checks if instruction has correct number of parameters
 *
 * @param token_array        array of token representing instruction
 * @param required_params    number of required parameters (0-3)
 */
function check_params_number($token_array, $required_params)
{
  if(count($token_array) - 1 != $required_params)
  {
    fwrite(STDERR, "ERROR:Other lexical or syntax error.\n");
    exit(23);
  }
}

/**
 * Checks if token is variable
 *
 * @param token     token to be checked
 */
function check_variable($token)
{
  if($token->type != "var")
  {
    fwrite(STDERR, "ERROR:Other lexical or syntax error.\n");
    exit(23);
  }
}

/**
 * Checks if token is label
 *
 * @param token     token to be checked
 */
function check_label($token)
{
  if($token->type != "label")
  {
    fwrite(STDERR, "ERROR:Other lexical or syntax error.\n");
    exit(23);
  }
}

/**
 * Checks if token is type
 *
 * @param token     token to be checked
 */
function check_type($token)
{
  if($token->type != "type")
  {
    fwrite(STDERR, "ERROR:Other lexical or syntax error.\n");
    exit(23);
  }
}

/**
 * Checks if token is symbol (variable or constant)
 *
 * @param token     token to be checked
 */
function check_symbol($token)
{
  if($token->type != "var" && $token->type != "const")
  {
    fwrite(STDERR, "ERROR:Other lexical or syntax error.\n");
    exit(23);
  }
}

/**
 * Analyze syntax of given array of tokens
 *
 * @param token_array     token array to be checked
 */
function syntax_analysis($token_array)
{
  // Checks opcode and then required arguments types
  switch ($token_array[0]->data)
  {
    // OPCODE <var> <symb>
    case "MOVE":
    case "INT2CHAR":
    case "STRLEN":
    case "TYPE":
    case "NOT":
      check_params_number($token_array, 2);
      check_variable($token_array[1]);
      check_symbol($token_array[2]);
      break;

    // OPCODE
    case "CREATEFRAME":
    case "PUSHFRAME":
    case "POPFRAME":
    case "RETURN":
    case "BREAK":
      check_params_number($token_array, 0);
      break;

    // OPCODE <var>
    case "DEFVAR":
    case "POPS":
      check_params_number($token_array, 1);
      check_variable($token_array[1]);
      break;

    // OPCODE <label>
    case "CALL":
    case "LABEL":
    case "JUMP":
      check_params_number($token_array, 1);
      check_label($token_array[1]);
      break;

    // OPCODE <symb>
    case "PUSHS":
    case "WRITE":
    case "EXIT":
    case "DPRINT":
      check_params_number($token_array, 1);
      check_symbol($token_array[1]);
      break;

    // OPCODE <var> <symb_1> <symb_2>
    case "ADD":
    case "SUB":
    case "MUL":
    case "IDIV":
    case "LT":
    case "GT":
    case "EQ":
    case "AND":
    case "OR":
    case "STRI2INT":
    case "CONCAT":
    case "STRLEN":
    case "GETCHAR":
    case "SETCHAR":
      check_params_number($token_array, 3);
      check_variable($token_array[1]);
      check_symbol($token_array[2]);
      check_symbol($token_array[3]);
      break;

    // OPCODE <var> <type>
    case "READ":
      check_params_number($token_array, 2);
      check_variable($token_array[1]);
      check_type($token_array[2]);
      break;

    // OPCODE <label> <symb_1> <symb_2>
    case "JUMPIFEQ":
    case "JUMPIFNEQ":
      check_params_number($token_array, 3);
      check_label($token_array[1]);
      check_symbol($token_array[2]);
      check_symbol($token_array[3]);
      break;

    // Unknown OPCODE -> ERROR
    default:
      fwrite(STDERR, "ERROR:Missing or invalid OPCODE.\n");
      exit(22);
      break;

  }
}

/**
 * Generates instructions in XML format
 *
 * @param token_array         token array to be converted to XML format
 * @param xml                 main xml root
 * @param $xml_program_node   program xml root
 */
function generate_xml($token_array, $xml, $xml_program_node)
{
  // Generate instruction in format <instruction order="$ORDER" opcode="$OPCODE"></instruction>
  $xml_instruction = $xml_program_node->appendChild($xml->createElement("instruction"));
  $xml_instruction->setAttribute("order", ++$GLOBALS['instruction_order']);
  $xml_instruction->setAttribute("opcode", $token_array[0]->data);

  // Generate arguments in format <arg$NUMBER type="$TYPE">$DATA</arg$NUMBER>
  foreach($token_array as $key => $value)
  {
    // Loop through token array without first index (OPCODE)
    if($key < 1)
    {
      continue;
    }

    // Constant must be split by '@' into type (left from '@') and value (right from '@')
    // htmlspecialchars() is used for converting problematic chars as &, <, >, ", ' into &amp;, &lt;, &gt;, &quot, &#039
    if($value->type == "const")
    {
      $parts = preg_split("/@/", $value->data, 2);
      $xml_argument = $xml_instruction->appendChild($xml->createElement("arg$key", htmlspecialchars($parts[1], ENT_QUOTES, 'UTF-8')));
      $xml_argument->setAttribute("type", $parts[0]);
    }
    else
    {
      $xml_argument = $xml_instruction->appendChild($xml->createElement("arg$key", htmlspecialchars($value->data)));
      $xml_argument->setAttribute("type", $value->type);
    }
  }
}


/**
 * Parses arguments given to the script via command line
 *
 * @param argv        script arguments
 */
function parse_arguments($argv)
{
  // Indicates invalid argument or invalid argument combination
  $error = false;

  // Loops through all arguments (except program name) and parses them
  foreach ($argv as $key => $arg)
  {
    if($key < 1)
    {
      continue;
    }
    if($arg == "--help")
    {
      if($GLOBALS['help'])
      {
        $error = true;
      }
      $GLOBALS['help'] = true;
    }
    elseif(preg_match("/^--(loc|comments|labels|jumps)$/", $arg))
    {
      $GLOBALS['stats_params'] = true;
    }
    elseif(preg_match("/^--stats=.+/", $arg))
    {
      if($GLOBALS['help'])
      {
        $error = true;
      }
      $GLOBALS['file_name'] = preg_replace("/--stats=/", "", $arg, 1);
      $GLOBALS['stat'] = true;
    }
    else
    {
      $error = true;
    }
  }

  // Invalid argument or invalid arguments combination -> ERROR
  if(($GLOBALS['stat'] && $GLOBALS['help']) || $error)
  {
    fwrite(STDERR, "ERROR:Invalid script arguments. Look php7.3 parse.php --help.\n");
    exit(10);
  }
  // --loc, --comments, --labels, --jumps arguments combined without --stats argument -> ERROR
  elseif(!$GLOBALS['stat'] && $GLOBALS['stats_params'])
  {
    fwrite(STDERR, "ERROR:Invalid script arguments. Look php7.3 parse.php --help.\n");
    exit(10);
  }
}


/***************************** MAIN PROGRAM *****************************/


parse_arguments($argv);

// Stats for STATP extension
$stats = new t_stats();

// Print help if required
if($GLOBALS['help'])
{
  print_help();
}
// Check for ".ippcode19" header in source code
$line = fgets(STDIN);
$line = $stats->handle_comments($line);
if(strtolower($line) != ".ippcode19")
{
  fwrite(STDERR, "ERROR:Missing .IPPcode19 header.\n");
  exit(21);
}

// XML header
$xml = new DOMDocument('1.0', 'UTF-8');
$xml->preserveWhiteSpace = false;
$xml->formatOutput = true;
$xml_program_node = $xml->appendChild($xml->createElement("program"));
$xml_program_node->setAttribute("language", "IPPcode19");

// Reads line by line from STDIN and verifies them
while($line = fgets(STDIN))
{
  $tokens = lexical_analysis($line, $stats);
  if(empty($tokens))
  {
    continue;
  }

  syntax_analysis($tokens);

  generate_xml($tokens, $xml, $xml_program_node);
}

// Print output XML
echo $xml->saveXML();

// Print stats if required
if($GLOBALS['stat'])
{
  $stats->print_stats($argv);
}
?>
