<?php

/** @file
 * This include file implements coder functionality for 4.7 -> 5.0 upgrades
 */

function coder_50_reviews() {
  $rules = array(
    array(
      '#type' => 'regex',
      '#value' => '\suser_mail\s*\(',
      '#warning_callback' => '_coder_50_user_mail_warning',
    ),
    array(
      '#type' => 'regex',
      '#value' => '\suser_mail_wrapper\s*\(',
      '#warning_callback' => '_coder_50_user_mail_wrapper_warning',
    ),
    array(
      '#type' => 'regex',
      '#value' => '\smessage_na\s*\(',
      '#warning_callback' => '_coder_50_message_na_warning',
    ),
    array(
      '#type' => 'regex',
      '#value' => '\smodule_exist\s*\(',
      '#warning_callback' => '_coder_50_module_exist_warning',
    ),
    array(
      '#type' => 'regex',
      '#value' => '\sdrupal_call_js\s*\(',
      '#warning_callback' => '_coder_50_drupal_call_js_warning',
    ),
    array(
      '#type' => 'regex',
      '#source' => 'all',
      '#value' => '\$_POST\s*\[\s*[\'"]?op[\'"]?\s*\]',
      '#warning' => '$_POST[\'op\'] deprecated in favor of $form_values[\'op\']',
    ),
    array(
      '#type' => 'callback',
      '#value' => _coder_50_callback,
    ),
    array(
      '#type' => 'regex',
      '#source' => 'all',
      '#value' => '\stheme_add_style\s*\(',
      '#warning_callback' => '_coder_50_theme_add_style_warning',
    ),
    array(
      '#type' => 'regex',
      '#source' => 'all',
      '#value' => '\sform_render\s*\(',
      '#warning_callback' => '_coder_50_form_render_warning',
    ),
  );
  $review = array(
    '#title' => t('Converting 4.7.x modules to 5.x'),
    '#link' => 'http://drupal.org/node/64279',
    '#rules' => $rules,
  );
  return array('upgrade50' => $review);
}

/**
 * Define the rule callbacks
 */

function _coder_50_callback(&$coder_args, $rule, $lines, &$results) {
  // only perform this check on module's (not includes)
  $filename = $coder_args['#filename'];
  if (substr($filename, -7) == '.module') {
    // make sure that a .info file exists
    $filename = drupal_substr(realpath($filename), 0, -7) .'.info';
    if (!file_exists($filename)) {
      $results[0] = theme('coder_warning', $lineno, t('All modules now need to have a <a href="@info">modulename.info file</a>', array('@info' => 'http://drupal.org/node/101009')));
    }
  }
}

/**
 * Define the warning callbacks
 */

function _coder_50_user_mail_warning() {
  return t('!user_mail() is replaced by !drupal_mail()',
    array(
      '!user_mail' => theme('drupalapi', 'user_mail', '4.7'),
      '!drupal_mail' => theme('drupalapi', 'drupal_mail'),
    )
  );
}

function _coder_50_drupal_mail_wrapper_warning() {
  return t('!user_mail_wrapper() changed to !drupal_mail_wrapper()',
    array(
      '!user_mail_wrapper' => theme('drupalapi', 'user_mail_wrapper', '4.7'),
      '!drupal_mail_wrapper' => theme('drupalapi', 'drupal_mail_wrapper'),
    )
  );
}

function _coder_50_message_na_warning() {
  return t('The function !message_na() was removed, remove it from your modules as well and replace it with !t(\'n/a\')',
    array(
      '!message_na' => theme('drupalapi', 'message_na', '4.7'),
      '!t' => theme('drupalapi', 't'),
    )
  );
}

function _coder_50_module_exist_warning() {
  return t('!module_exist() is now !module_exists()',
    array(
      '!module_exist' => theme('drupalapi', 'module_exist', '4.7'),
      '!module_exists' => theme('drupalapi', 'module_exists'),
    )
  );
}

function _coder_50_drupal_call_js_warning() {
  return t('Remove !drupal_call_js(), use "!drupal_add_js(\'myCustomFunction(your, parameters, here)\', \'inline\');" instead',
    array(
      '!drupal_call_js' => theme('drupalapi', 'drupal_call_js', '4.7'),
      '!drupal_add_js' => theme('drupalapi', 'drupal_add_js'),
    )
  );
}

function _coder_50_theme_add_style_warning() {
  return t('Replace !theme_add_style() with !drupal_add_css()',
    array(
      '!theme_add_style' => theme('drupalapi', 'theme_add_style', '4.7'),
      '!drupal_add_css' => theme('drupalapi', 'drupal_add_css'),
    )
  );
}

function _coder_50_form_render_warning() {
  return t('Replace !form_render() with !drupal_render()',
    array(
      '!form_render' => theme('drupalapi', 'form_render', '4.7'),
      '!drupal_render' => theme('drupalapi', 'drupal_render'),
    )
  );
}
