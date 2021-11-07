/*
 * canvas.h
 *
 *  Created on: 22 de out de 2021
 *      Author: Filipe Chagas
 */

#ifndef PENCIL_H
#define PENCIL_H

#include <stdint.h>
#include "displays/display.hpp"
#include "glyph.hpp"
#include "font.hpp"
#include "color.hpp"
#include "image.hpp"
#include "rectangle.hpp"

/**
 * @brief The Pencil class is responsible for drawing and filling things on a Display
 * without anti-aliasing and alpha-composition. If you want anti-aliasing and alpha-composition
 * use BufferedPencil.
 */
class Pencil
{
protected:
    Display *display;
    int w, h;

public:
    /**
     * @brief Construct a new Pencil object.
     * 
     * @param display Display object where the Pencil class will draw things.
     */
    Pencil(Display &display);

    /**
     * @brief Draw a pixel.
     * 
     * @param x X-axis pixel location.
     * @param y Y-axis pixel location.
     * @param color Color to print.
     */
    virtual void drawPixel(float x, float y, Color color);

    /**
     * @brief Draw a line between two points.
     * 
     * @param x1 X coordinate of first point. 
     * @param y1 Y coordinate of first point.
     * @param x2 X coordinate of second point.
     * @param y2 Y coordinate of second point.
     * @param color Line color.
     */
    void drawLine(float x1, float y1, float x2, float y2, Color color);

    /**
     * @brief Draw a rectangle.
     * 
     * @param x X-axis rectangle location.
     * @param y Y-axis rectangle location.
     * @param w Rectangle width.
     * @param h Rectangle height.
     * @param color Rectangle color.
     */
    void drawRectangle(float x, float y, float w, float h, Color color);

    /**
     * @brief Draw a circle.
     * 
     * @param x X coordinate to circle centroid.
     * @param y Y coordinate to circle centroid.
     * @param radius Circle radius.
     * @param color Circle color.
     * @param vertices (Optional) Number of vertices around the circunference. Default is 100.
     */
    void drawCircle(float x, float y, float radius, Color color, uint32_t vertices = 100);

    /**
     * @brief Draw a ellipse.
     * 
     * @param x X coordinate to ellipse centroid.
     * @param y Y coordinate to ellipse centroid.
     * @param w Ellipse width.
     * @param h Ellipse height.
     * @param color Ellipse color.
     * @param vertices (Optional) Number of vertices around the ellipse. Default is 100.
     */
    void drawEllipse(float x, float y, float w, float h, Color color, uint32_t vertices = 100);
    
    /**
     * @brief Draw a arc between theta1 and theta2 rotation points.
     * the arc is drawn clockwise if ``theta2 > theta1`` and counterclockwise if ``theta1 > theta2``.
     * @param x X coordinate to arc origin. 
     * @param y Y coordinate to arc origin.
     * @param theta1 Initial rotation point (in radians).
     * @param theta2 Final rotation point (in radians).
     * @param radius Arc radius.
     * @param color Arc color.
     * @param vertices (Optional) Number of vertices around the arc. Default is 100.
     */
    void drawArc(float x, float y, float theta1, float theta2, float radius, Color color, uint32_t vertices = 100);
    
    /**
     * @brief Draw a rectangle with rounded edges.
     * 
     * @param x X-axis rectangle location.
     * @param y Y-axis rectangle location.
     * @param w Rectangle width.
     * @param h Rectangle height.
     * @param radius Edges radius.
     * @param color Rectangle color.
     * @param edge_vertices (Optional) Number of vertices around edges arcs. Default is 100.
     */
    void drawRoundedRectangle(float x, float y, float w, float h, float radius, Color color, uint32_t edge_vertices = 100);

    /**
     * @brief Draw a polygon.
     * 
     * @param x_array Vertices x-axis array (sorted counterclockwise around centroid).
     * @param y_array Vertices y-axis array (sorted counterclockwise around centroid).
     * @param len  Arrays length.
     * @param color Polygon color.
     */
    void drawPolygon(float *x_array, float *y_array, uint32_t len, Color color);

    /**
     * @brief draw a Glyph
     *
     * @param x X coordinate to the glyph location.
     * @param y Y coordinate to the glyph location.
     * @param glyph Reference to the Glyph object.
     * @param color Color to print the glyph.
     */
    void drawGlyph(float x, float y, Glyph &glyph, Color color);

    /**
     * @brief Draw a char.
     * 
     * @param x X-axis char location.
     * @param y Y-axis char location.
     * @param c Char.
     * @param font Char font.
     * @param color Char color.
     * @return Rectangle of the affected area.
     */
    Rectangle drawChar(float x, float y, char c, Font &font, Color color);

#ifndef EXCLUDE_DEFAULT_FONT
    /**
     * @brief Draw a char (default font).
     * @param x X-axis char location.
     * @param y Y-axis char location.
     * @param c Char.
     * @param color Char color.
     * @return Rectangle of the affected area.
     */
    Rectangle drawChar(float x, float y, char c, Color color);
#endif

    /**
     * @brief Draw text.
     * 
     * @param x X-axis text location.
     * @param y Y-axis text location.
     * @param text Text
     * @param font Text font.
     * @param color Text color.
     * @return Rectangle of the affected area.
     */
    Rectangle drawText(float x, float y, const char* text, Font &font, Color color, float h_spacing = 1, float v_spacing = 1);

#ifndef EXCLUDE_DEFAULT_FONT
    /**
     * @brief Draw text (default font).
     * @param x X-axis text location.
     * @param y Y-axis text location.
     * @param text Text.
     * @param color Text color.
     * @return Rectangle of the affected area.
     */
    Rectangle drawText(float x, float y, const char* text, Color color, float h_spacing = 0, float v_spacing = 4);
#endif

    /**
     * @brief Draw a Image.
     * 
     * @param x X-axis image location.
     * @param y Y-axis image location.
     * @param image Image object.
     */
    void drawImage(float x, float y, Image &image);

    /**
     * @brief Fill a rectangle with a single color.
     * 
     * @param x X-axis rectangle location.
     * @param y Y-axis rectangle location.
     * @param w Rectangle width.
     * @param h Rectangle height.
     * @param color Rectangle color.
     */
    void fillRectangle(float x, float y, float w, float h, Color color);
    
    /**
     * @brief Fill a circle with a single color.
     * 
     * @param x X coordinate to circle centroid.
     * @param y Y coordinate to circle centroid.
     * @param radius Circle radius.
     * @param color Circle color.
     */
    void fillCircle(float x, float y, float radius, Color color);

    /**
     * @brief Fill a ellipse with a single color.
     * 
     * @param x X coordinate to ellipse centroid.
     * @param y Y coordinate to ellipse centroid.
     * @param w Ellipse width.
     * @param h Ellipse height.
     * @param color Ellipse color.
     */
    void fillEllipse(float x, float y, float w, float h, Color color);

    /**
     * @brief Fill a polygon with a single color.
     *
     * @param x_array Vertices x-axis array (sorted counterclockwise around centroid).
     * @param y_array Vertices y-axis array (sorted counterclockwise around centroid).
     * @param len  Arrays length.
     * @param color Polygon color.
     */
    void fillPolygon(float *x_array, float *y_array, uint32_t len, Color color);

    /**
     * @brief Draw a sector between theta1 and theta2 rotation points.
     * the sector is drawn clockwise if ``theta2 > theta1`` and counterclockwise if ``theta1 > theta2``.
     * @param x X coordinate to sector origin. 
     * @param y Y coordinate to sector origin.
     * @param theta1 Initial rotation point (in radians).
     * @param theta2 Final rotation point (in radians).
     * @param radius Sector radius.
     * @param color Sector color.
     * @param vertices (Optional) Number of vertices around the sector. Default is 100.
     */
    void fillSector(float x, float y, float theta1, float theta2, float radius, Color color, uint32_t vertices = 100);

    /**
     * @brief Fill a rectangle with rounded edges.
     * 
     * @param x X-axis rectangle location.
     * @param y Y-axis rectangle location.
     * @param w Rectangle width.
     * @param h Rectangle height.
     * @param radius Edges radius.
     * @param color Rectangle color.
     * @param edge_vertices (Optional) Number of vertices around edges arcs. Default is 100.
     */
    void fillRoundedRectangle(float x, float y, float w, float h, float radius, Color color, uint32_t edge_vertices = 100);

    /**
     * @brief Destroy the Pencil object.
     * 
     */
    virtual ~Pencil();
};

#endif /* PENCIL_H */
