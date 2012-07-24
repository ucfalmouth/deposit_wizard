<?php

/*
 * page callback to provide view of user's research or a 'my-research' editing page
 * ($parent is supplied from url by hook_menu if available)
 */
function deposit_wizard_depositpage ($pid = NULL) {
  global $user;
  // we could predict previously deposited types here
  // just redirect to the node add page for the moment
  
  // TODO: theming for twitter bootstrap or equivalent to simplify page (eg below)
  // libraries_load('twitter_bootstrap');
  // drupal_add_js('$(".collapse").collapse()', 'inline');
  
  $instructions = 'Select the type of content you would like to deposit';
  $page = array();
  $page[] = '<p>'. t($instructions) .'</p>';
  
  $content_type_groups = ContentTypeGroup::fetch(TRUE);
  foreach ($content_type_groups as $group) {
      if (preg_match("/refcategory_/", $group->type)) {
        $id = 'group-'.str_replace('_','-',$group->type);
        //drupal_add_js('jQuery("#'.$id.'").collapse()', 'inline');
        //$page[] = '<div data-toggle="collapse" data-target="#'.$id.'"><h2>'. $group->name .'</h2></div>';
        //$page[] = '<div id="'.$id.'" class="collapse">'. deposit_wizard_node_links($pid, $group) .'</div>';
        $page[] = '<div class="lilo">';
        $page[] = '<div><h2>'. $group->name .'</h2></div>';
        $page[] = '<div id="'.$id.'" class="refcategory">'. deposit_wizard_node_links($pid, $group) .'</div>';
        $page[] = '</div>';
      }
  }

  

  //$page = 'hello';
  return implode("\n", $page);
}

// content creation 
// returns links that will prepopulate a node reference (using nodereference_url module)
function deposit_wizard_node_links($pid = NULL, $group = NULL) {
  if ($pid) { $parent = node_load($pid); }
  if (!$group) { $group = new ContentTypeGroup('deposit'); }

  $items = array();
  foreach($group->typeList() as $type => $name){
    if ($pid) {
      $parent = node_load($pid);
      $items[] = nodereference_url_create_link($parent, 'field_researchgroup', $type);
    } else {
      $items[] = l($name, "node/add/".str_replace('_','-', $type));
    }
  }
  
  return theme('item_list', array('items' => $items));
}

