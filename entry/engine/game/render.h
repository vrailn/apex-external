#pragma once
#include <apex/entry/imgui/imgui_impl_win32.h>
#include <apex/entry/imgui/imgui_internal.h>
#include <apex/entry/imgui/imgui.h>

namespace wiget {

	bool slider_float(const char* label, float* v, float v_min, float v_max)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *ImGui::GetCurrentContext();
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);

		float width = 140.0f;
		float height = 6.0f;

		ImVec2 pos = ImGui::GetCursorScreenPos();
		ImVec2 label_pos = ImVec2(pos.x, pos.y + 2.0f);
		ImVec2 slider_pos = ImVec2(pos.x, pos.y + 22.0f);
		ImRect bb(slider_pos, ImVec2(slider_pos.x + width, slider_pos.y + height));
		ImGui::ItemSize(ImVec2(width, 22));
		if (!ImGui::ItemAdd(bb, id))
			return false;

		if (label && label[0] != '\0') {
			ImGui::GetWindowDrawList()->AddText(label_pos, IM_COL32(255, 255, 255, 255), label);
		}

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held);
		if (held) {
			float mouse_x = ImGui::GetIO().MousePos.x;
			float t = (mouse_x - bb.Min.x) / (bb.Max.x - bb.Min.x);
			t = ImClamp(t, 0.0f, 1.0f);
			*v = ImLerp(v_min, v_max, t);
		}

		float t = (*v - v_min) / (v_max - v_min);
		float filled_width = t * width;

		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		ImU32 bg_col = IM_COL32(30, 30, 30, 255);
		ImU32 fill_col = IM_COL32(90, 120, 255, 255);

		draw_list->AddRectFilled(bb.Min, bb.Max, bg_col, 0.0f);
		draw_list->AddRectFilled(bb.Min, ImVec2(bb.Min.x + filled_width, bb.Max.y), fill_col, 0.0f);
		draw_list->AddRect(bb.Min, bb.Max, IM_COL32(120, 120, 120, 255), 0.0f);

		float handle_x = bb.Min.x + filled_width;
		float handle_size = height + 2.0f;
		ImVec2 handle_min(handle_x - handle_size * 0.5f, bb.Min.y - 1.0f);
		ImVec2 handle_max(handle_x + handle_size * 0.5f, bb.Max.y + 1.0f);
		draw_list->AddRectFilled(handle_min, handle_max, IM_COL32(90, 120, 255, 255), 0.0f);
		draw_list->AddRect(handle_min, handle_max, IM_COL32(255, 255, 255, 255), 0.0f);

		char buf[32];
		snprintf(buf, sizeof(buf), "%.1f", *v);
		ImVec2 val_text_size = ImGui::CalcTextSize(buf);
		float value_x = bb.Max.x + 12.0f;
		float value_y = bb.Min.y + (height * 0.5f) - (val_text_size.y * 0.5f);
		draw_list->AddText(ImVec2(value_x, value_y), IM_COL32(255, 255, 255, 255), buf);

		return held;
	}

	bool slider_int(const char* label, int* v, int v_min, int v_max, float width = 150.0f, float height = 6.0f)
	{
		float float_val = static_cast<float>(*v);
		bool changed = slider_float(label, &float_val, static_cast<float>(v_min), static_cast<float>(v_max));
		*v = static_cast<int>(float_val + 0.5f);
		return changed;
	}

	bool check_box(const char* label, bool* v, float boxSize = 20.0f)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *ImGui::GetCurrentContext();
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);

		ImVec2 pos = ImGui::GetCursorScreenPos();
		ImRect box_bb(pos, ImVec2(pos.x + boxSize, pos.y + boxSize));
		ImGui::ItemSize(box_bb);
		if (!ImGui::ItemAdd(box_bb, id))
			return false;

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(box_bb, id, &hovered, &held);
		if (pressed)
			*v = !*v;

		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		ImU32 border_col = hovered ? IM_COL32(90, 120, 255, 255) : IM_COL32(80, 80, 80, 255);
		ImU32 fill_col = *v ? IM_COL32(90, 120, 255, 255) : IM_COL32(30, 30, 30, 255);

		draw_list->AddRectFilled(box_bb.Min, box_bb.Max, fill_col, 0.0f);
		draw_list->AddRect(box_bb.Min, box_bb.Max, border_col, 0.0f, 0, 2.0f);

		if (*v) {
			float pad = boxSize * 0.25f;
			ImVec2 p1 = ImVec2(box_bb.Min.x + pad, box_bb.Min.y + boxSize * 0.55f);
			ImVec2 p2 = ImVec2(box_bb.Min.x + boxSize * 0.45f, box_bb.Max.y - pad);
			ImVec2 p3 = ImVec2(box_bb.Max.x - pad, box_bb.Min.y + pad);
			draw_list->AddLine(p1, p2, IM_COL32(255, 255, 255, 255), 2.5f);
			draw_list->AddLine(p2, p3, IM_COL32(255, 255, 255, 255), 2.5f);
		}

		if (label && label[0] != '\0') {
			ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
			ImGui::TextUnformatted(label);
		}

		return pressed;
	}

	bool color_picker(const char* label, float color[3], float box_size = 16.0f)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		const ImGuiID id = window->GetID(label);
		const ImGuiStyle& style = ImGui::GetStyle();
		const ImVec2 pos = ImGui::GetCursorScreenPos();
		ImVec2 box_min = pos;
		ImVec2 box_max = ImVec2(pos.x + box_size, pos.y + box_size);

		ImRect bb(box_min, box_max);
		ImGui::ItemSize(bb);
		if (!ImGui::ItemAdd(bb, id))
			return false;

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held);
		bool changed = false;

		ImU32 col = IM_COL32(
			(int)(color[0] * 255),
			(int)(color[1] * 255),
			(int)(color[2] * 255),
			255
		);

		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		draw_list->AddRectFilled(box_min, box_max, col, 3.0f);
		draw_list->AddRect(box_min, box_max, hovered ? IM_COL32(90, 120, 255, 255) : IM_COL32(100, 100, 100, 255), 3.0f);

		ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
		ImGui::TextUnformatted(label);

		if (pressed)
			ImGui::OpenPopup(label);

		if (ImGui::BeginPopup(label)) {
			changed |= ImGui::ColorPicker3("##picker", color,
				ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview | ImGuiColorEditFlags_NoInputs);
			ImGui::EndPopup();
		}

		return changed;
	}

	bool combo_box(const char* label, int* current_item, const char* const items[], int items_count, float width = 150.0f)
	{
		ImVec4 blue = ImVec4(0.353f, 0.471f, 1.0f, 1.0f);

		ImGui::GetStyle().Colors[ImGuiCol_Header] = blue;
		ImGui::GetStyle().Colors[ImGuiCol_HeaderHovered] = ImVec4(0.4f, 0.52f, 1.0f, 1.0f);
		ImGui::GetStyle().Colors[ImGuiCol_HeaderActive] = ImVec4(0.45f, 0.57f, 1.0f, 1.0f);
		ImGui::GetStyle().Colors[ImGuiCol_Button] = blue;
		ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImVec4(0.4f, 0.52f, 1.0f, 1.0f);
		ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = ImVec4(0.45f, 0.57f, 1.0f, 1.0f);
		ImGui::GetStyle().Colors[ImGuiCol_FrameBgHovered] = blue;
		ImGui::GetStyle().Colors[ImGuiCol_FrameBgActive] = ImVec4(0.45f, 0.57f, 1.0f, 1.0f);

		if (label && label[0] != '\0') {
			ImGui::TextUnformatted(label);
		}

		ImGui::SetNextItemWidth(width);
		bool changed = false;
		if (ImGui::BeginCombo("##combo", items[*current_item])) {
			for (int i = 0; i < items_count; ++i) {
				bool is_selected = (i == *current_item);
				if (ImGui::Selectable(items[i], is_selected)) {
					*current_item = i;
					changed = true;
				}
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

		return changed;
	}


}

namespace draw {


	void AddHexagon(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& p5, const ImVec2& p6, ImU32 col, float thickness)
	{
		if ((col & IM_COL32_A_MASK) == 0)
			return;

		ImGui::GetBackgroundDrawList()->PathLineTo(p1);
		ImGui::GetBackgroundDrawList()->PathLineTo(p2);
		ImGui::GetBackgroundDrawList()->PathLineTo(p3);
		ImGui::GetBackgroundDrawList()->PathLineTo(p4);
		ImGui::GetBackgroundDrawList()->PathLineTo(p5);
		ImGui::GetBackgroundDrawList()->PathLineTo(p6);

		ImGui::GetBackgroundDrawList()->PathStroke(col, true, thickness);
	}

	void AddHexagonFilled(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& p5, const ImVec2& p6, ImU32 col)
	{
		if ((col & IM_COL32_A_MASK) == 0)
			return;

		ImGui::GetBackgroundDrawList()->PathLineTo(p1);
		ImGui::GetBackgroundDrawList()->PathLineTo(p2);
		ImGui::GetBackgroundDrawList()->PathLineTo(p3);
		ImGui::GetBackgroundDrawList()->PathLineTo(p4);
		ImGui::GetBackgroundDrawList()->PathLineTo(p5);
		ImGui::GetBackgroundDrawList()->PathLineTo(p6);
		ImGui::GetBackgroundDrawList()->PathFillConvex(col);
	}

	void DrawQuadFilled(ImVec2 p1, ImVec2 p2, ImVec2 p3, ImVec2 p4, ImColor color) {
		ImGui::GetBackgroundDrawList()->AddQuadFilled(p1, p2, p3, p4, color);
	}

	void DrawHexagon(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& p5, const ImVec2& p6, ImU32 col, float thickness)
	{
		AddHexagon(p1, p2, p3, p4, p5, p6, col, thickness);
	}

	void DrawHexagonFilled(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& p5, const ImVec2& p6, ImU32 col)
	{
		AddHexagonFilled(p1, p2, p3, p4, p5, p6, col);
	}



	void DrawRectFilled(const ImVec2& min, const ImVec2& max, ImColor color) {
		ImDrawList* drawList = ImGui::GetBackgroundDrawList(); 
		drawList->AddRectFilled(min, max, color);
	}
	ImColor GetShieldColor(int armorType) {
		switch (armorType) {
		case 1: return ImColor(247, 247, 247);
		case 2: return ImColor(39, 178, 255);
		case 3: return ImColor(206, 59, 255);
		case 4: return ImColor(255, 255, 79);
		case 5: return ImColor(219, 2, 2);
		default: return ImColor(247, 247, 247);
		}
	}
	void SeerHealth(float x, float y, int shield, int max_shield, int armorType, int health,
		float width = 80.0f, float height = 14.0f) {
		float max_health = 100.0f;
		float shield_step = 25.0f;
		int segments = 5;

		float shield_height = height * 0.35f;
		float health_height = height - shield_height;
		float padding = 2.0f;

		ImVec2 bg_min(x - width / 2, y - height);
		ImVec2 bg_max(x + width / 2, y);
		DrawRectFilled(bg_min, bg_max, ImColor(0, 0, 0, 180));

		ImVec2 health_bg_min(bg_min.x + padding, bg_min.y + padding + shield_height);
		ImVec2 health_bg_max(bg_max.x - padding, bg_max.y - padding);
		DrawRectFilled(health_bg_min, health_bg_max, ImColor(20, 20, 50, 100));

		float health_width = (float)health / max_health * (width - 2 * padding);
		ImVec2 health_min(health_bg_min.x, health_bg_min.y);
		ImVec2 health_max(health_bg_min.x + health_width, health_bg_max.y);
		DrawRectFilled(health_min, health_max, ImColor(0, 255, 0, 255));

		ImColor shieldCracked(97, 97, 97);
		ImColor shieldCol = GetShieldColor(armorType);

		int shieldRemaining = shield;
		float segmentWidth = (width - 2 * padding) / segments;

		for (int i = 0; i < segments; ++i) {
			ImVec2 seg_min(health_bg_min.x + i * segmentWidth,
				health_bg_min.y - shield_height);
			ImVec2 seg_max(seg_min.x + segmentWidth, seg_min.y + shield_height);

			DrawRectFilled(seg_min, seg_max, shieldCracked);

			if (shieldRemaining > 0) {
				float shieldWidth = (float)min(shieldRemaining, 25) / shield_step * segmentWidth;
				ImVec2 shield_max(seg_min.x + shieldWidth, seg_max.y);
				DrawRectFilled(seg_min, shield_max, shieldCol);
			}

			shieldRemaining -= 25;
		}
	}



	void DrawTextWithOutline(ImDrawList* drawList, ImFont* font, float fontSize, ImVec2 pos, ImU32 textColor, ImU32 outlineColor, const char* text, bool outline, float thickness = 1.0f) {
		if (outline)
		{
			drawList->AddText(font, fontSize, ImVec2(pos.x - thickness, pos.y - thickness), outlineColor, text);
			drawList->AddText(font, fontSize, ImVec2(pos.x + thickness, pos.y - thickness), outlineColor, text);
			drawList->AddText(font, fontSize, ImVec2(pos.x - thickness, pos.y + thickness), outlineColor, text);
			drawList->AddText(font, fontSize, ImVec2(pos.x + thickness, pos.y + thickness), outlineColor, text);
		}
		drawList->AddText(font, fontSize, pos, textColor, text);
	}

	void DrawRotatedImageWithBoxColor(ImTextureID textureID, float x, float y, float width, float height, ImColor tintColor)
	{
		ImVec2 center = ImVec2(x + width * 0.5f, y + height * 0.5f);

		float angle = 3.14159265359f;

		ImVec2 rotationMatrix[2] = {
			ImVec2(cos(angle), -sin(angle)),
			ImVec2(sin(angle), cos(angle))
		};

		auto calculateRotatedCoordinates = [&](ImVec2 point) -> ImVec2 {
			return ImVec2(
				center.x + rotationMatrix[0].x * (point.x - center.x) + rotationMatrix[0].y * (point.y - center.y),
				center.y + rotationMatrix[1].x * (point.x - center.x) + rotationMatrix[1].y * (point.y - center.y)
			);
			};

		ImVec2 topLeft = ImVec2(x, y);
		ImVec2 bottomRight = ImVec2(x + width, y + height);

		ImVec2 rotatedTopLeft = calculateRotatedCoordinates(topLeft);
		ImVec2 rotatedBottomRight = calculateRotatedCoordinates(bottomRight);

		ImVec2 offset[8] = {
		ImVec2(-1, -1), ImVec2(1, -1), ImVec2(-1, 1), ImVec2(1, 1),
		ImVec2(-1, 0), ImVec2(1, 0), ImVec2(0, -1), ImVec2(0, 1)
		};

		for (int i = 0; i < 8; i++) {
			ImVec2 outlineTopLeft = ImVec2(rotatedTopLeft.x + offset[i].x, rotatedTopLeft.y + offset[i].y);
			ImVec2 outlineBottomRight = ImVec2(rotatedBottomRight.x + offset[i].x, rotatedBottomRight.y + offset[i].y);
			ImGui::GetBackgroundDrawList()->AddImage(textureID, outlineTopLeft, outlineBottomRight, ImVec2(0, 0), ImVec2(1, 1), IM_COL32(0, 0, 0, 255));
		}
		ImGui::GetBackgroundDrawList()->AddImage(textureID, rotatedTopLeft, rotatedBottomRight, ImVec2(0, 0), ImVec2(1, 1), ImGui::ColorConvertFloat4ToU32(tintColor));

	}

	void draw_normal_box(float x, float y, float w, float h, ImColor color, float thickness) {

		ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), ImColor(0, 0, 0), 0, -1, (thickness * 3));

		ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, -1, thickness);
	}

	void draw_text(float x, float y, ImColor color, const char* string, ...) {
		char buf[512];
		va_list arg_list;

		ZeroMemory(buf, sizeof(buf));

		va_start(arg_list, string);
		vsnprintf(buf, sizeof(buf), string, arg_list);
		va_end(arg_list);

		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(x, y), color, buf, 0, 0, 0);
		return;
	}

	void draw_line(float x, float y, float x2, float y2, ImColor color, float thickness) {
		if (x < 0)
			return;

		if (y < 0)
			return;

		if (x2 > (float)Width)
			return;

		if (y2 > (float)Height)
			return;

		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y), ImVec2(x2, y2), color, thickness);
		return;
	}

	void draw_rectangle(float x, float y, float x2, float y2, ImColor color, float thickness) {
		ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + x2, y + y2), color, 0, -1, thickness);
		return;
	}

	void draw_cornered_box(int x, int y, int w, int h, const ImColor color, int thickness)
	{

		ImGui::GetForegroundDrawList()->AddLine(ImVec2(x, y), ImVec2(x, y + (h / 3)), ImColor(0, 0, 0), (thickness * 3));
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(x, y), ImVec2(x + (w / 3), y), ImColor(0, 0, 0), (thickness * 3));
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(x + w - (w / 3), y), ImVec2(x + w, y), ImColor(0, 0, 0), (thickness * 3));
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(x + w, y), ImVec2(x + w, y + (h / 3)), ImColor(0, 0, 0), (thickness * 3));
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(x, y + h - (h / 3)), ImVec2(x, y + h), ImColor(0, 0, 0), (thickness * 3));
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(x, y + h), ImVec2(x + (w / 3), y + h), ImColor(0, 0, 0), (thickness * 3));
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(x + w - (w / 3), y + h), ImVec2(x + w, y + h), ImColor(0, 0, 0), (thickness * 3));
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(x + w, y + h - (h / 3)), ImVec2(x + w, y + h), ImColor(0, 0, 0), (thickness * 3));

		ImGui::GetForegroundDrawList()->AddLine(ImVec2(x, y), ImVec2(x, y + (h / 3)), color, thickness);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(x, y), ImVec2(x + (w / 3), y), color, thickness);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(x + w - (w / 3), y), ImVec2(x + w, y), color, thickness);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(x + w, y), ImVec2(x + w, y + (h / 3)), color, thickness);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(x, y + h - (h / 3)), ImVec2(x, y + h), color, thickness);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(x, y + h), ImVec2(x + (w / 3), y + h), color, thickness);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(x + w - (w / 3), y + h), ImVec2(x + w, y + h), color, thickness);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(x + w, y + h - (h / 3)), ImVec2(x + w, y + h), color, thickness);
	}

	void draw_rectangle_filled(float x, float y, float x2, float y2, ImColor color) {
		ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + x2, y + y2), color);
		return;
	}

	void draw_rectangle_filled_multicolor(float x, float y, float x2, float y2, ImColor color, ImColor color2, ImColor color3, ImColor color4) {
		ImGui::GetBackgroundDrawList()->AddRectFilledMultiColor(ImVec2(x, y), ImVec2(x + x2, y + y2), color, color2, color3, color4);
		return;
	}

	void draw_corner_box(float x, float y, float x2, float y2, ImColor color, float thickness) {
		float box_width = x2 - x;
		float box_height = y2 - y;

		draw_line(x, y, x + box_width / 4, y, color, thickness);
		draw_line(x2, y, x2 - box_width / 4, y, color, thickness);

		draw_line(x, y, x, y + box_height / 3, color, thickness);
		draw_line(x, y2, x, y2 - box_height / 3, color, thickness);

		draw_line(x2, y, x2, y + box_height / 3, color, thickness);
		draw_line(x2, y2, x2, y2 - box_height / 3, color, thickness);

		draw_line(x, y2, x + box_width / 4, y2, color, thickness);
		draw_line(x2, y2, x2 - box_width / 4, y2, color, thickness);

		return;
	}

	void draw_circle(float x, float y, ImColor color, float radius) {
		ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(x, y), radius, color);
		return;
	}

	void draw_filled_circle(float x, float y, ImColor color, float radius) {
		ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(x, y), radius, color);
		return;
	}
	inline void DrawMinecraftNametag(float x, float y, const char* name, ImColor bgColor = ImColor(0, 0, 0, 180), ImColor borderColor = ImColor(0, 0, 0, 255), ImColor textColor = ImColor(255, 255, 255, 255))
	{
		ImDrawList* drawList = ImGui::GetBackgroundDrawList();
		ImFont* font = ImGui::GetFont();
		float fontSize = ImGui::GetFontSize();

		ImVec2 textSize = ImGui::CalcTextSize(name);
		float paddingX = 6.0f;
		float paddingY = 2.0f;

		ImVec2 boxMin(x - textSize.x / 2 - paddingX, y - textSize.y / 2 - paddingY);
		ImVec2 boxMax(x + textSize.x / 2 + paddingX, y + textSize.y / 2 + paddingY);

		drawList->AddRectFilled(boxMin, boxMax, bgColor, 0.0f);

		drawList->AddRect(boxMin, boxMax, borderColor, 0.0f, 0, 1.5f);

		drawList->AddText(font, fontSize, ImVec2(x - textSize.x / 2, y - textSize.y / 2), textColor, name);
	}
	inline void draw_arrow(const ImVec2& pos, float angle, float size, ImColor color) {
		ImDrawList* draw_list = ImGui::GetForegroundDrawList();

		ImVec2 tip = ImVec2(
			pos.x + cosf(angle) * size,
			pos.y + sinf(angle) * size
		);
		ImVec2 left = ImVec2(
			pos.x + cosf(angle + 2.5f) * (size * 0.5f),
			pos.y + sinf(angle + 2.5f) * (size * 0.5f)
		);
		ImVec2 right = ImVec2(
			pos.x + cosf(angle - 2.5f) * (size * 0.5f),
			pos.y + sinf(angle - 2.5f) * (size * 0.5f)
		);

		draw_list->AddTriangleFilled(tip, left, right, color);
		draw_list->AddTriangle(tip, left, right, ImColor(0, 0, 0, 255), 2.0f);
	}
}