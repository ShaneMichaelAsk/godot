#include "lightfield_gi_editor_plugin.h"

#include "core/object/class_db.h"
#include "editor/editor_node.h"
#include "editor/editor_string_names.h"
#include "editor/plugins/editor_plugin.h"
#include "scene/gui/button.h"
#include "scene/3d/lightfield_gi.h"

bool LightfieldGIEditorPlugin::bake_func_step(float p_progress, const String& p_description, void*,
															bool p_refresh)
{
	return false;
}

void LightfieldGIEditorPlugin::bake_func_end(uint64_t p_time_started)
{

}

void LightfieldGIEditorPlugin::_bake_select_file(const String &p_file)
{

}

void LightfieldGIEditorPlugin::_bake()
{
	print_line("Bake!");
}

void LightfieldGIEditorPlugin::_bind_methods()
{
	ClassDB::bind_method("_bake", &LightfieldGIEditorPlugin::_bake);
}

void LightfieldGIEditorPlugin::edit(Object *p_object)
{
	LightfieldGI *s = Object::cast_to<LightfieldGI>(p_object);
	if (!s) { return; }

	lightfield = s;
}

bool LightfieldGIEditorPlugin::handles(Object* p_object) const
{
	return p_object->is_class("LightfieldGI");
}

void LightfieldGIEditorPlugin::make_visible(bool p_visible)
{
	if (p_visible) { bake->show(); }
	else { bake->hide(); }
}

LightfieldGIEditorPlugin::LightfieldGIEditorPlugin()
{
	print_line("LightfieldGIEditorPlugin");

	bake = memnew(Button);
	bake->set_theme_type_variation(SceneStringName(FlatButton));
	bake->set_button_icon(EditorNode::get_singleton()->get_editor_theme()->get_icon(SNAME("Bake"), EditorStringName(EditorIcons)));
	bake->set_text(TTR("Bake Lightfield"));

	bake->hide();
	bake->connect(SceneStringName(pressed), Callable(this, "_bake"));
	add_control_to_container(CONTAINER_SPATIAL_EDITOR_MENU, bake);
}
