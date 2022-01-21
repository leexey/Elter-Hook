#pragma once

namespace StreamProofESP
{
	struct box {
		int x, y, w, h;
		box() = default;
		box(int x, int y, int w, int h) {
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}
	};

    void render() noexcept;
	void run();
	void SurfaceHealth(Entity* entity);
	void SurfaceHealth2(Entity* entity);
	void rendersurface() noexcept;
	void updateInput() noexcept;

    // GUI
    void menuBarItem() noexcept;
    void tabItem() noexcept;
    void drawGUI(bool contentOnly) noexcept;
}
