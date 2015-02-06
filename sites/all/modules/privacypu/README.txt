Privacy Per User
----------------
Privacy Per User provides a simple framework to enable privacy settings per user, similar to the privacy settings on a site like Facebook.

Installation
------------
Install as you would any other module, copy it to the appropriate modules directory and enable the Privacy Per User module. You may optionally enable the 'Privacy Per User: Profile' module if you would like to enable privacy settings for user profile pages. And the 'Privacy Per User: Flag Friend' module if you are using Flag Friend and would like to enable the 'Share with friends only' privacy state.

Usage
-----
The module does its work via a single access function, privacypu_check_access() and one hook, hook_privacypu_states_info(). The access function may be used in hook_menu(), a preprocess function, or anywhere you would like to check whether the current user should have access to another user's stuff. You can define the types of stuff that you would like users to set privacy preferences on using the UI at 'admin/build/privacypu'. The hook, hook_privacypu_states_info(), defines which privacy states should be available for a user to select from. By default the available states are 'public' and 'private'. Enabling the Flag Friend integration module adds an additional 'friends only' state.

The default privacy state, that is to say the privacy state before a user has had a chance to choose, is configurable globally via an admin settings page, as well as per type.

Defining Privacy Types
----------------------
Defining privacy types via hook_privacypu_types_info() has been deprecated in favor of using CTools exportables, so that privacy types may be defined via a UI and exported if desired, either manually using the export option or through Features. Use the UI at 'admin/build/privacypu' to create, edit, and manage your privacy types. If you have previously configured any privacy types via the hook, they will be imported into the database when you run update.php with the latest version. You may then either export them or continue to use them directly from the database. The hook will no longer be used after the update is run, so you should feel free to delete your implementation(s) of it after that.

Views
-----
A Views argument validator plugin is included which allows you to easily validate a user ID argument in your view against privacy settings. The typical use case for this is for a view of user specific content, something like a track page, bookmarks, a friends list, etc. You first need to define a privacy type in the UI. Then you can add a uid argument to your view, set the validator to Privacy Per User, select the privacy type that you defined, and set the action to take if the argument does not validate to 'hide view / page not found (404)'.

Checking Access
---------------
The access function privacypu_check_access() requires two arguments, a user object and the machine name of a privacy type. It also takes a third optional argument, a permission which may be useful for setting a baseline level of privacy. For example, when displaying user profiles you might want 'Share with everyone' to really mean 'Share with everyone who is an authenticated user', in which case you can set the 'access user profiles' permission just for authenticated users. Since the profile integration module is passing that permission into privacypu_check_access() it would not display profiles to anonymous users regardless of an individual user's privacy settings.

Defining Privacy States
-----------------------
The default privacy states are 'public' (Share with everyone), 'private' (Do not share), and if the flag friend integration module is enabled, 'friend' (Share with friends only). It is possible that you require more privacy states. Perhaps you use something other than Flag Friend to define relationships among your users. Or perhaps you would like a 'Share with friends of friends' option. Using hook_privacypu_states_info() it is easy to define additional privacy states.

Refer to the included privacypu_flag_friend module for a good example. Here is a generalized version of the hook:

  /**
   * Implements hook_privacypu_states_info().
   */
  function my_module_privacypu_states_info() {
    $states = array(
      'my_privacy_state' => array(
        'title' => t('My privacy state'),
        'callback' => 'my_module_privacy_state',
      ),
      'another_privacy_state' => array(
        'title' => t('Another Privacy State'),
        'callback' => 'my_module_another_privacy_state',
      ),
    );

    return $states;
  }

To make this work for you: change 'my_module' in the function name to reflect the name of your module, change 'my_privacy_state' to reflect the machine name of your privacy state, and change the title 'My privacy state' to reflect the human readable name of your privacy state. Change 'my_module_privacy_state' to reflect the name of the callback function for your privacy state. You may add as many states to the hook as you like.

The callback function should take one argument, the user object for the account whose privacy settings are being checked. It should return true if the current user should be given access or false if not.

Author
------
Brendan Andersen
brendan@omnifik.com